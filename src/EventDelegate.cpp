//
// Created by Enlil on 7/18/2022.
//

#include "EventDelegate.h"

namespace caepe {

    EventDelegate::EventDelegate(EventManager &eventManager)
            : _eventManager(eventManager)
    {
    }

    Result EventDelegate::subscribe(Component &component)
    {
        return _eventManager.subscribe(component);
    }

} // caepe