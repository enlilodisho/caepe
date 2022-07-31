//
// Created by Enlil on 7/30/2022.
//

#include <caepe/ActionResponse.h>

#include <gtest/gtest.h>

TEST(ActionResponseTest, ActionResponseMessageTest)
{
    caepe::ActionResponse actionResponse1 { caepe::ACTION_RESPONSE_NONE };
    ASSERT_EQ(actionResponse1._message, caepe::ACTION_RESPONSE_NONE);
    caepe::ActionResponse actionResponse2 { caepe::ACTION_RESPONSE_SUCCESS };
    ASSERT_EQ(actionResponse2._message, caepe::ACTION_RESPONSE_SUCCESS);
}

TEST(ActionResponseTest, DefaultMessageTest)
{
    caepe::ActionResponse actionResponse;
    ASSERT_EQ(actionResponse._message, caepe::ACTION_RESPONSE_UNDEFINED);
}