//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_COMPONENT_H
#define CAEPE_COMPONENT_H

#include <string>

namespace caepe {

    class Component {
    public:
        const std::string _name;

        explicit Component(std::string name);
    };

} // caepe

#endif //CAEPE_COMPONENT_H
