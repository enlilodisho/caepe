//
// Created by Enlil on 7/18/2022.
//

#ifndef CAEPE_EVENTDELEGATE_H
#define CAEPE_EVENTDELEGATE_H

#include "EventManager.h"

#include <vector>

namespace caepe
{

    class Component;

    class EventDelegate {
    private:
        EventManager& _eventManager;

    public:
        explicit EventDelegate(EventManager &eventManager);

        Result subscribe(Component &component);
    };

} // caepe

#endif //CAEPE_EVENTDELEGATE_H
