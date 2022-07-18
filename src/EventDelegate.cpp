//
// Created by Enlil on 7/18/2022.
//

#include "EventDelegate.h"

namespace caepe {

    EventDelegate::EventDelegate(EventHandler &eventHandler)
            : _eventHandler(eventHandler)
    {
    }

    Result EventDelegate::subscribe(Component &component)
    {
        return _eventHandler.subscribe(component);
    }

} // caepe