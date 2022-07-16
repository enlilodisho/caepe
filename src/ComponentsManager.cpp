//
// Created by Enlil on 7/16/2022.
//

#include "ComponentsManager.h"
#include "Result.h"

namespace caepe
{

    Result ComponentsManager::addComponent(std::unique_ptr<Component> component)
    {
        _components.push_back(std::move(component));
        return Result(RESULT_OK);
    }

    const std::vector<std::unique_ptr<Component>>& ComponentsManager::getComponents() const
    {
        return _components;
    }

} // caepe