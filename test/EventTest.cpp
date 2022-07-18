//
// Created by Enlil on 7/17/2022.
//
#include <caepe/Event.h>

#include <gtest/gtest.h>

TEST(EventTest, EventNameFieldTest)
{
    caepe::Event event { "Event1" };
    ASSERT_EQ(event._name, "Event1");
}