//
// Created by Enlil on 7/15/2022.
//
#include "ComponentMock.h"

#include <caepe/Result.h>
#include <caepe/Event.h>

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

TEST(ComponentTest, ComponentAddEventTest)
{
    ComponentMock component1("SomeComponent");
    component1.start();

    std::shared_ptr<caepe::Event> event = std::make_shared<caepe::Event>();
    event->_name = "SomeEvent";
    ComponentMock senderComponent("SenderComponent");
    ASSERT_EQ(component1.addEvent(&senderComponent, event).getValue(), caepe::RESULT_OK);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto receivedEvents = component1.getReceivedEvents();
    ASSERT_EQ(receivedEvents.size(), 1);
    ASSERT_EQ(receivedEvents[0].first, &senderComponent);
    ASSERT_EQ(receivedEvents[0].second.get(), event.get());
}