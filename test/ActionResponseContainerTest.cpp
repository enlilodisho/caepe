//
// Created by Enlil on 7/31/2022.
//

#include <caepe/ActionResponseContainer.h>
#include <caepe/ActionResponse.h>

#include <gtest/gtest.h>

TEST(ActionResponseContainerTest, GetActionResponseWithoutSettingTest)
{
    caepe::ActionResponseContainer responseContainer;
    ASSERT_EQ(responseContainer.getActionResponse(), nullptr);
}

TEST(ActionResponseContainerTest, SetAndGetActionResponseTest)
{
    caepe::ActionResponseContainer responseContainer;
    std::unique_ptr<caepe::ActionResponse> actionResponse = std::make_unique<caepe::ActionResponse>("DummyResponse");
    ASSERT_EQ(responseContainer.setActionResponse(std::move(actionResponse)).getValue(), caepe::RESULT_OK);
    ASSERT_NE(responseContainer.getActionResponse(), nullptr);
    ASSERT_EQ(responseContainer.getActionResponse()->getMessage(), "DummyResponse");
}

TEST(ActionResponseContainerTest, SetActionResponseTwiceFailsTest)
{
    caepe::ActionResponseContainer responseContainer;
    std::unique_ptr<caepe::ActionResponse> actionResponse = std::make_unique<caepe::ActionResponse>("DummyResponse1");
    ASSERT_EQ(responseContainer.setActionResponse(std::move(actionResponse)).getValue(), caepe::RESULT_OK);
    actionResponse = std::make_unique<caepe::ActionResponse>("DummyResponse2");
    ASSERT_EQ(responseContainer.setActionResponse(std::move(actionResponse)).getValue(), caepe::RESULT_ERROR);
    ASSERT_NE(responseContainer.getActionResponse(), nullptr);
    ASSERT_EQ(responseContainer.getActionResponse()->getMessage(), "DummyResponse1");
}

TEST(ActionResponseContainerTest, IsResponseSetTest)
{
    caepe::ActionResponseContainer responseContainer;
    ASSERT_FALSE(responseContainer.isResponseSet());
    std::unique_ptr<caepe::ActionResponse> actionResponse = std::make_unique<caepe::ActionResponse>("DummyResponse");
    ASSERT_EQ(responseContainer.setActionResponse(std::move(actionResponse)).getValue(), caepe::RESULT_OK);
    ASSERT_TRUE(responseContainer.isResponseSet());
}