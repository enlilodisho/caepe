//
// Created by Enlil on 7/18/2022.
//

#ifndef CAEPE_EVENTHANDLER_H
#define CAEPE_EVENTHANDLER_H

#include "Event.h"
#include "Result.h"

#include <vector>
#include <memory>
#include <mutex>

namespace caepe
{

    class Component;

    class EventHandler {
    private:
        std::mutex _mtx;
        std::vector<Component*> _subscribers;

    public:
        Result subscribe(Component &component);
        Result post(Component* sender, std::unique_ptr<Event> event);
    };

} // caepe
#endif //CAEPE_EVENTHANDLER_H
