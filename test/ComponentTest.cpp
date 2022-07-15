//
// Created by Enlil on 7/15/2022.
//
#include "ComponentMock.h"

#include <gtest/gtest.h>

TEST(ComponentTest, ComponentNameCheck)
{
    ComponentMock component1("SomeComponent");
    ASSERT_EQ(component1._name, "SomeComponent");
}