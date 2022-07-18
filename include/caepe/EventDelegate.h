//
// Created by Enlil on 7/18/2022.
//

#ifndef CAEPE_EVENTDELEGATE_H
#define CAEPE_EVENTDELEGATE_H

#include "EventHandler.h"

#include <vector>

namespace caepe
{

    class Component;

    class EventDelegate {
    private:
        EventHandler& _eventHandler;

    public:
        explicit EventDelegate(EventHandler &eventHandler);

        Result subscribe(Component &component);
    };

} // caepe

#endif //CAEPE_EVENTDELEGATE_H
