//
// Created by Enlil on 7/15/2022.
//
#include "ComponentMock.h"

#include <caepe/Result.h>

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

TEST(ComponentTest, ComponentNameCheck)
{
    ComponentMock component1("SomeComponent");
    ASSERT_EQ(component1._name, "SomeComponent");
}

TEST(ComponentTest, StartComponentTest)
{
    ComponentMock component1("SomeComponent");
    ASSERT_FALSE(component1.isStarted());
    ASSERT_EQ(0, component1.getOnStartRunCount());
    ASSERT_EQ(0, component1.getOnLoopRunCount());
    ASSERT_EQ(0, component1.getOnEndRunCount());

    ASSERT_EQ(caepe::RESULT_OK, component1.start().getValue());
    ASSERT_TRUE(component1.isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ASSERT_EQ(1, component1.getOnStartRunCount());
    ASSERT_TRUE(component1.getOnLoopRunCount() > 0);
    ASSERT_EQ(0, component1.getOnEndRunCount());

    ASSERT_EQ(caepe::RESULT_OK, component1.stop().getValue());
    ASSERT_FALSE(component1.isStarted());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(1, component1.getOnEndRunCount());
}