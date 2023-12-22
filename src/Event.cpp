//
// Created by Enlil Odisho on 12/22/23.
//

#include "Event.h"

namespace caepe
{

    Event::Event(std::string name)
            : _name(std::move(name))
    {
    }

    Event::~Event() = default;

} // caepe