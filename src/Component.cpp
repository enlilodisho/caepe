//
// Created by Enlil on 7/15/2022.
//

#include "Component.h"
#include "Result.h"

namespace caepe {

    Component::Component(std::string name)
        : _name(std::move(name))
    {
    }

    Component::~Component()
    {
        stop();
    }

    Result Component::start()
    {
        std::lock_guard<std::mutex> lock(_startStopMtx);
        if (_started)
        {
            return {RESULT_OK, "Component is already running."};
        }
        _started = true;
        _thread = std::make_unique<std::thread>(&Component::componentThread, this);
        return Result(RESULT_OK);
    }

    Result Component::stop()
    {
        std::lock_guard<std::mutex> lock(_startStopMtx);
        if (!_started)
        {
            return {RESULT_OK, "Component is already not running."};
        }
        _started = false;
        _thread->join();
        return Result(RESULT_OK);
    }

    [[maybe_unused]]
    Result Component::receiveEvent(Component *sender, std::shared_ptr<const Event> event)
    {
        std::lock_guard lock(_eventsMtx);
        _pendingEvents.emplace(sender, std::move(event));
        return Result(RESULT_OK);
    }

    [[maybe_unused]]
    Result Component::receiveAction(Component *sender, std::unique_ptr<Action> action,
                                    std::shared_ptr<Action> &out_action)
    {
        std::shared_ptr action_shared = std::move(action);
        std::lock_guard lock(_actionsMtx);
        _pendingActions.emplace(sender, action_shared);
        out_action = action_shared;
        return Result(RESULT_OK);
    }

    void Component::onStart()
    {
    }

    void Component::onLoop()
    {
    }

    void Component::onAction(Component &sender, std::shared_ptr<Action> action,
                             std::shared_ptr<ActionResponseContainer> responseContainer)
    {
    }

    void Component::onEvent(Component& sender, std::shared_ptr<const Event> event)
    {
    }

    void Component::onEnd()
    {
    }

    void Component::componentThread()
    {
        onStart();
        while (_started)
        {
            onLoop();

            // check pending action responses
            {
                auto it = _pendingActionResponses.begin();
                while (it != _pendingActionResponses.end())
                {
                    auto& action = std::get<0>(*it);
                    if (action->isResponseSet())
                    {
                        it = _pendingActionResponses.erase(it);
                        continue;
                    }
                    auto& actionResponseContainer = std::get<1>(*it);
                    auto& startingResponseContainerCopyCount = std::get<2>(*it);
                    if (actionResponseContainer.use_count() == startingResponseContainerCopyCount)
                    {
                        actionResponseContainer->setActionResponse(
                                std::make_unique<ActionResponse>(ACTION_RESPONSE_NONE));
                        it = _pendingActionResponses.erase(it);
                    }
                    else
                    {
                        it++;
                    }
                }
            }

            // process actions if any available
            {
                std::lock_guard lock(_actionsMtx);
                while (!_pendingActions.empty())
                {
                    std::shared_ptr<Action> action = std::move(_pendingActions.front().second);
                    std::shared_ptr<ActionResponseContainer> actionResponseContainer =
                            std::make_shared<ActionResponseContainer>();
                    action->setResponseContainer(actionResponseContainer);
                    long startingResponseContainerCopyCount = actionResponseContainer.use_count();
                    onAction(*_pendingActions.front().first, action, actionResponseContainer);

                    if (!action->isResponseSet())
                    {
                        if (actionResponseContainer.use_count() == startingResponseContainerCopyCount)
                        {
                            actionResponseContainer->setActionResponse(
                                    std::make_unique<ActionResponse>(ACTION_RESPONSE_NONE));
                        }
                        else
                        {
                            _pendingActionResponses.emplace_back(std::move(action),
                                                                 std::move(actionResponseContainer),
                                                            startingResponseContainerCopyCount);
                        }
                    }

                    _pendingActions.pop();
                }
            }

            // process events if any available
            {
                std::lock_guard lock(_eventsMtx);
                while (!_pendingEvents.empty())
                {
                    onEvent(*_pendingEvents.front().first, std::move(_pendingEvents.front().second));
                    _pendingEvents.pop();
                }
            }
        }
        onEnd();
    }

    bool Component::isStarted() const
    {
        return _started;
    }

} // caepe