//
// Created by Enlil on 7/18/2022.
//

#include "EventManager.h"
#include "Component.h"

#include <algorithm>

namespace caepe {

    Result EventManager::subscribe(Component &component)
    {
        std::lock_guard lock(_mtx);
        if (std::find(_subscribers.begin(), _subscribers.end(), &component) == _subscribers.end())
        {
            _subscribers.push_back(&component);
            return Result(RESULT_OK);
        }
        else
        {
            return {RESULT_OK, "Component is already subscribed to this EventManager."};
        }
    }

    Result EventManager::post(Component* sender, std::unique_ptr<Event> event)
    {
        std::shared_ptr event_shared = std::move(event);
        std::lock_guard lock(_mtx);
        for (Component* component : _subscribers)
        {
            component->receiveEvent(sender, event_shared);
        }
        return Result(RESULT_OK);
    }

} // caepe