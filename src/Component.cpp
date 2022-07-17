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
        std::lock_guard<std::mutex> lock(_mtx);
        if (_started)
        {
            stop();
        }
    }

    Result Component::start()
    {
        std::lock_guard<std::mutex> lock(_mtx);
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
        std::lock_guard<std::mutex> lock(_mtx);
        if (!_started)
        {
            return {RESULT_OK, "Component is already not running."};
        }
        _started = false;
        _thread->join();
        return Result(RESULT_OK);
    }

    void Component::onStart()
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
            onLoop();
        }
        onEnd();
    }

    bool Component::isStarted() const
    {
        return _started;
    }

} // caepe