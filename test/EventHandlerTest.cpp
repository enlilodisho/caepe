//
// Created by Enlil on 7/18/2022.


#include "ComponentMock.h"

#include <caepe/Event.h>
#include <caepe/EventHandler.h>
#include <caepe/Result.h>

#include <gtest/gtest.h>
#include <memory>
#include <chrono>
#include <thread>

TEST(EventHandlerTest, EventHandlerSubscribeAndPostTest)
{
    ComponentMock senderComponent("SenderComponent");
    ComponentMock component1("Component1");
    component1.start();
    caepe::EventHandler eventHandler;
    ASSERT_EQ(eventHandler.subscribe(component1).getValue(), caepe::RESULT_OK);
    auto event = std::make_unique<caepe::Event>();
    event->_name = "Event1";
    ASSERT_EQ(eventHandler.post(&senderComponent, std::move(event)).getValue(), caepe::RESULT_OK);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto receivedEvents = std::move(component1.getReceivedEvents());
    ASSERT_TRUE(receivedEvents.size() == 1);
    ASSERT_EQ(receivedEvents[0].first, &senderComponent);
    ASSERT_EQ(receivedEvents[0].second->_name, "Event1");
}