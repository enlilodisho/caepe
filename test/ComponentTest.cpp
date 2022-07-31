//
// Created by Enlil on 7/15/2022.
//
#include "ComponentMock.h"

#include <caepe/Result.h>
#include <caepe/Event.h>

#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <tuple>

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

TEST(ComponentTest, ComponentReceiveEventTest)
{
    ComponentMock component1("SomeComponent");
    component1.start();

    std::shared_ptr<caepe::Event> event = std::make_shared<caepe::Event>();
    event->_name = "SomeEvent";
    ComponentMock senderComponent("SenderComponent");
    ASSERT_EQ(component1.receiveEvent(&senderComponent, event).getValue(), caepe::RESULT_OK);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto receivedEvents = component1.getReceivedEvents();
    ASSERT_EQ(receivedEvents.size(), 1);
    ASSERT_EQ(receivedEvents[0].first, &senderComponent);
    ASSERT_EQ(receivedEvents[0].second.get(), event.get());
}

TEST(ComponentTest, ComponentReceiveActionTest)
{
    ComponentMock component1("SomeComponent");
    component1.start();

    ComponentMock senderComponent("SenderComponent");
    std::shared_ptr<caepe::Action> action;
    ASSERT_EQ(component1.receiveAction(&senderComponent,
                                       std::move(std::make_unique<caepe::Action>("DummyAction")),
                                       action).getValue(), caepe::RESULT_OK);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto receivedActions = component1.getReceivedActions();
    ASSERT_EQ(receivedActions.size(), 1);
    ASSERT_EQ(std::get<0>(receivedActions[0]), &senderComponent);
    ASSERT_EQ(std::get<1>(receivedActions[0])->getName(), "DummyAction");
    ASSERT_EQ(action.get(), std::get<1>(receivedActions[0]).get());
}

TEST(ComponentTest, ComponentRespondsToActionTest) {
    ComponentMock component1("SomeComponent");
    component1.start();

    ComponentMock senderComponent("SenderComponent");
    std::shared_ptr<caepe::Action> action;
    {
        std::unique_ptr tempActionPtr = std::make_unique<caepe::Action>("DummyAction");
        caepe::ActionResponse actionResponse;
        ASSERT_EQ(tempActionPtr->getResponse(actionResponse).getValue(), caepe::RESULT_ERROR);
        ASSERT_EQ(component1.receiveAction(&senderComponent,
                                           std::move(tempActionPtr),
                                           action).getValue(), caepe::RESULT_OK);
    }

    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto receivedActions = component1.getReceivedActions();
        ASSERT_EQ(receivedActions.size(), 1);
        std::unique_ptr<caepe::ActionResponse> actionResponse
                = std::make_unique<caepe::ActionResponse>("DummyResponse");
        std::get<2>(receivedActions[0])->setActionResponse(std::move(actionResponse));
    }

    {
        caepe::ActionResponse actionResponse;
        ASSERT_EQ(action->getResponse(actionResponse).getValue(), caepe::RESULT_OK);
        ASSERT_EQ(actionResponse._message, "DummyResponse");
    }
}

TEST(ComponentTest, ComponentSetsResponseToNoneWhenContainerCopyIsDeleted)
{
    ComponentMock component1("SomeComponent");
    component1.start();

    ComponentMock senderComponent("SenderComponent");
    std::shared_ptr<caepe::Action> action;
    {
        std::unique_ptr tempActionPtr = std::make_unique<caepe::Action>("DummyAction");
        ASSERT_EQ(component1.receiveAction(&senderComponent,
                                           std::move(tempActionPtr),
                                           action).getValue(), caepe::RESULT_OK);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_FALSE(action->isResponseSet());
    caepe::ActionResponse actionResponse;
    ASSERT_EQ(action->getResponse(actionResponse).getValue(), caepe::RESULT_ERROR);
    ASSERT_EQ(actionResponse._message, caepe::ACTION_RESPONSE_UNDEFINED);

    {
        auto receivedActions = component1.getReceivedActions();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ASSERT_FALSE(action->isResponseSet());
        ASSERT_EQ(action->getResponse(actionResponse).getValue(), caepe::RESULT_ERROR);
        ASSERT_EQ(actionResponse._message, caepe::ACTION_RESPONSE_UNDEFINED);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_TRUE(action->isResponseSet());
    ASSERT_EQ(action->getResponse(actionResponse).getValue(), caepe::RESULT_OK);
    ASSERT_EQ(actionResponse._message, caepe::ACTION_RESPONSE_NONE);
}