//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_COMPONENTMOCK_H
#define CAEPE_COMPONENTMOCK_H

#include <caepe/Component.h>
#include <caepe/Event.h>
#include <caepe/Action.h>
#include <caepe/ActionResponseContainer.h>

#include <vector>
#include <tuple>
#include <utility>
#include <mutex>

class ComponentMock : public caepe::Component
{
private:
    long _ranOnStart = 0;
    long _ranOnLoop = 0;
    long _ranOnEnd = 0;

    std::vector<std::tuple<Component*, std::shared_ptr<caepe::Action>,
            std::shared_ptr<caepe::ActionResponseContainer>>> _receivedActions;
    std::vector<std::pair<Component*, std::shared_ptr<const caepe::Event>>> _receivedEvents;
    std::mutex _actionsMtx;
    std::mutex _eventsMtx;

protected:
    void onStart() override
    {
        _ranOnStart++;
    }

    void onLoop() override
    {
        _ranOnLoop++;
    }

    void onAction(Component &sender, std::shared_ptr<caepe::Action> action,
                  std::shared_ptr<caepe::ActionResponseContainer> responseContainer) override
    {
        std::lock_guard lock(_actionsMtx);
        _receivedActions.emplace_back(&sender, std::move(action), std::move(responseContainer));
    }

    void onEvent(Component &sender, std::shared_ptr<const caepe::Event> event) override
    {
        std::lock_guard lock(_eventsMtx);
        _receivedEvents.emplace_back(&sender, std::move(event));
    }

    void onEnd() override
    {
        _ranOnEnd++;
    }

public:
    explicit ComponentMock(const std::string& name) : caepe::Component(name)
    {
    }

    [[nodiscard]]
    long getOnStartRunCount() const
    {
        return _ranOnStart;
    }

    [[nodiscard]]
    long getOnLoopRunCount() const
    {
        return _ranOnLoop;
    }

    [[nodiscard]]
    long getOnEndRunCount() const
    {
        return _ranOnEnd;
    }

    [[nodiscard]]
    std::vector<std::tuple<Component*, std::shared_ptr<caepe::Action>,
            std::shared_ptr<caepe::ActionResponseContainer>>> getReceivedActions()
    {
        std::lock_guard lock(_actionsMtx);
        auto v = std::move(_receivedActions);
        _receivedActions = std::vector<std::tuple<Component*, std::shared_ptr<caepe::Action>,
                std::shared_ptr<caepe::ActionResponseContainer>>>();
        return std::move(v);
    }

    [[nodiscard]]
    std::vector<std::pair<Component*, std::shared_ptr<const caepe::Event>>> getReceivedEvents()
    {
        std::lock_guard lock(_eventsMtx);
        auto v = std::move(_receivedEvents);
        _receivedEvents = std::vector<std::pair<Component*, std::shared_ptr<const caepe::Event>>>();
        return std::move(v);
    }
};

#endif //CAEPE_COMPONENTMOCK_H
