//
// Created by Enlil on 7/18/2022.
//

#ifndef CAEPE_EVENTDELEGATE_H
#define CAEPE_EVENTDELEGATE_H

#include "EventHandler.h"

#include <vector>

namespace caepe
{

    //class Component;

    class EventDelegate {
    private:
        EventHandler& _eventHandler;
        //std::vector<Component*> _subscribers;

    public:
        explicit EventDelegate(EventHandler &eventHandler);
    };

} // caepe

#endif //CAEPE_EVENTDELEGATE_H
