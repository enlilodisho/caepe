//
// Created by Enlil on 7/18/2022.
//

#ifndef CAEPE_EVENTMANAGER_H
#define CAEPE_EVENTMANAGER_H

#include "Event.h"
#include "Result.h"

#include <vector>
#include <memory>
#include <mutex>

namespace caepe
{

    class Component;

    class EventManager {
    private:
        std::mutex _mtx;
        std::vector<Component*> _subscribers;

    public:
        Result subscribe(Component &component);
        Result post(Component* sender, std::unique_ptr<Event> event);
    };

} // caepe
#endif //CAEPE_EVENTMANAGER_H
