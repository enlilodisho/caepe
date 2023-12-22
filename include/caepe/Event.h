//
// Created by Enlil on 7/17/2022.
//

#ifndef CAEPE_EVENT_H
#define CAEPE_EVENT_H

#include <string>

namespace caepe {

    struct Event
    {
        explicit Event(std::string name);
        virtual ~Event();

        std::string _name;
    };

} // caepe

#endif //CAEPE_EVENT_H
