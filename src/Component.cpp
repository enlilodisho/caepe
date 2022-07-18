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

    Result Component::addEvent(Component *sender, std::shared_ptr<const Event> event)
    {
        std::lock_guard lock(_eventsMtx);
        _pendingEvents.emplace(sender, event);
        return Result(RESULT_OK);
    }

    void Component::onStart()
    {
    }

    void Component::onEvent(Component& sender, std::shared_ptr<const Event> event)
    {
    }

    void Component::onLoop()
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
            {
                std::lock_guard lock(_eventsMtx);
                while (!_pendingEvents.empty())
                {
                    onEvent(*_pendingEvents.front().first, std::move(_pendingEvents.front().second));
                    _pendingEvents.pop();
                }
            }
            onLoop();
        }
        onEnd();
    }

    bool Component::isStarted() const
    {
        return _started;
    }

} // caepe