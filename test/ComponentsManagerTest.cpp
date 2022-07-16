//
// Created by Enlil on 7/16/2022.
//
#include <caepe/ComponentsManager.h>
#include <caepe/Component.h>

#include <gtest/gtest.h>

TEST(ComponentsManagerTest, AddAndGetComponentsTest)
{
    caepe::ComponentsManager componentsManager;
    ASSERT_EQ(componentsManager.getComponents().size(), 0);

    std::unique_ptr<caepe::Component> component = std::make_unique<caepe::Component>("SomeComponent");
    ASSERT_EQ(caepe::RESULT_OK, componentsManager.addComponent(std::move(component)).getValue());
    auto& components = componentsManager.getComponents();
    ASSERT_EQ(components.size(), 1);
    ASSERT_EQ(components[0]->_name, "SomeComponent");
}