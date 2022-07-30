//
// Created by Enlil on 7/18/2022.
//

#include "ComponentMock.h"

#include <caepe/EventDelegate.h>

#include <gtest/gtest.h>
#include <thread>
#include <chrono>

TEST(EventDelegateTest, EventDelegateSubscribeTest)
{
    caepe::EventManager eventManager;
    caepe::EventDelegate eventDelegate(eventManager);

    ComponentMock subscriberComponent("SubscriberComponent");
    subscriberComponent.start();
    ASSERT_EQ(eventDelegate.subscribe(subscriberComponent).getValue(), caepe::RESULT_OK);

    std::unique_ptr<caepe::Event> event = std::make_unique<caepe::Event>();
    event->_name = "Event1";
    ComponentMock senderComponent("SenderComponent");
    eventManager.post(&senderComponent, std::move(event));

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto receivedEvents = subscriberComponent.getReceivedEvents();
    ASSERT_EQ(receivedEvents.size(), 1);
    ASSERT_EQ(receivedEvents[0].first, &senderComponent);
    ASSERT_EQ(receivedEvents[0].second->_name, "Event1");
}