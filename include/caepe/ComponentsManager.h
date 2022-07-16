//
// Created by Enlil on 7/16/2022.
//

#ifndef CAEPE_COMPONENTSMANAGER_H
#define CAEPE_COMPONENTSMANAGER_H

#include "Result.h"
#include "Component.h"

#include <memory>
#include <vector>

namespace caepe
{

    class ComponentsManager {
    protected:
        std::vector<std::unique_ptr<Component>> _components;

    public:
        Result addComponent(std::unique_ptr<Component> component);

        [[nodiscard]]
        const std::vector<std::unique_ptr<Component>>& getComponents() const;
    };

} // caepe

#endif //CAEPE_COMPONENTSMANAGER_H
