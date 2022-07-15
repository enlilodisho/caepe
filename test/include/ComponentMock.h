//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_COMPONENTMOCK_H
#define CAEPE_COMPONENTMOCK_H

#include <caepe/Component.h>

class ComponentMock : public caepe::Component
{
public:
    explicit ComponentMock(const std::string& name) : caepe::Component(name)
    {

    }
};

#endif //CAEPE_COMPONENTMOCK_H
