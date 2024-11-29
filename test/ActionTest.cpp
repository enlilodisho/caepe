//
// Created by Enlil on 7/29/2022.
//
#include <caepe/Action.h>
#include <caepe/ActionResponse.h>
#include <caepe/ActionResponseContainer.h>

#include <gtest/gtest.h>

TEST(ActionTest, ActionNameFieldTest)
{
    caepe::Action action { "DummyAction" };
    ASSERT_EQ(action.getName(), "DummyAction");
}

TEST(ActionTest, ActionParametersFieldTest)
{
    caepe::Action actionWithoutParams { "DummyActionWithoutParameters" };
    EXPECT_TRUE(actionWithoutParams.getParameters().empty());

    caepe::Action actionWithParams { "DummyActionWithParams", {10, 1.3f, 4.24, 'a', "test message" }};
    auto& params = actionWithParams.getParameters();
    ASSERT_GE(params.size(), 5);
    EXPECT_EQ(params.size(), 5);
    ASSERT_TRUE(std::holds_alternative<int>(params[0]));
    EXPECT_EQ(std::get<int>(params[0]), 10);
    ASSERT_TRUE(std::holds_alternative<float>(params[1]));
    EXPECT_EQ(std::get<float>(params[1]), 1.3f);
    ASSERT_TRUE(std::holds_alternative<double>(params[2]));
    EXPECT_EQ(std::get<double>(params[2]), 4.24);
    ASSERT_TRUE(std::holds_alternative<char>(params[3]));
    EXPECT_EQ(std::get<char>(params[3]), 'a');
    ASSERT_TRUE(std::holds_alternative<std::string>(params[4]));
    EXPECT_EQ(std::get<std::string>(params[4]), "test message");
}

TEST(ActionTest, ActionSetResponseContainerTest)
{
    caepe::Action action { "Action" };
    caepe::ActionResponse actionResponse;
    std::shared_ptr<caepe::ActionResponseContainer> responseContainer
        = std::make_shared<caepe::ActionResponseContainer>();
    ASSERT_EQ(action.getResponse(actionResponse).getValue(), caepe::RESULT_ERROR);
    ASSERT_EQ(action.setResponseContainer(responseContainer).getValue(), caepe::RESULT_OK);
    ASSERT_EQ(action.getResponse(actionResponse).getValue(), caepe::RESULT_ERROR);
    responseContainer->setActionResponse(std::make_unique<caepe::ActionResponse>("Response"));
    ASSERT_EQ(action.getResponse(actionResponse).getValue(), caepe::RESULT_OK);
    ASSERT_EQ(actionResponse._message, "Response");
}

TEST(ActionTest, ActionSetSameResponseContainerTwiceTest)
{
    caepe::Action action { "Action" };
    std::shared_ptr<caepe::ActionResponseContainer> responseContainer = std::make_shared<caepe::ActionResponseContainer>();
    ASSERT_EQ(action.setResponseContainer(responseContainer).getValue(), caepe::RESULT_OK);
    ASSERT_EQ(action.setResponseContainer(responseContainer).getValue(), caepe::RESULT_OK);
}

TEST(ActionTest, ActionSetResponseContainerFailsWhenAlreadySetToAnotherContainerTest)
{
    caepe::Action action { "Action" };
    std::shared_ptr<caepe::ActionResponseContainer> responseContainer1
        = std::make_shared<caepe::ActionResponseContainer>();
    responseContainer1->setActionResponse(std::make_unique<caepe::ActionResponse>("Response1"));
    std::shared_ptr<caepe::ActionResponseContainer> responseContainer2
            = std::make_shared<caepe::ActionResponseContainer>();
    responseContainer2->setActionResponse(std::make_unique<caepe::ActionResponse>("Response2"));
    ASSERT_EQ(action.setResponseContainer(responseContainer1).getValue(),
              caepe::RESULT_OK);
    ASSERT_EQ(action.setResponseContainer(responseContainer2).getValue(),
              caepe::RESULT_ERROR);
    caepe::ActionResponse actionResponse;
    ASSERT_EQ(action.getResponse(actionResponse).getValue(), caepe::RESULT_OK);
    ASSERT_EQ(actionResponse._message, "Response1");
}

TEST(ActionTest, ActionIsResponseSetTest)
{
    caepe::Action action { "Action" };
    ASSERT_FALSE(action.isResponseSet());
    std::shared_ptr<caepe::ActionResponseContainer> responseContainer = std::make_shared<caepe::ActionResponseContainer>();
    action.setResponseContainer(responseContainer);
    ASSERT_FALSE(action.isResponseSet());
    responseContainer->setActionResponse(std::make_unique<caepe::ActionResponse>(caepe::ACTION_RESPONSE_NONE));
    ASSERT_TRUE(action.isResponseSet());
}