//
// Created by Enlil on 7/30/2022.
//

#include <caepe/ActionResponse.h>

#include <gtest/gtest.h>
#include <string>
#include <typeinfo>
#include <vector>

TEST(ActionResponseTest, ActionResponseMessageTest)
{
    caepe::ActionResponse actionResponse1 { caepe::ActionResponse::NONE };
    EXPECT_EQ(actionResponse1.getMessage(), caepe::ActionResponse::NONE);
    EXPECT_FALSE(actionResponse1.hasData());
    caepe::ActionResponse actionResponse2 { caepe::ActionResponse::SUCCESS };
    EXPECT_EQ(actionResponse2.getMessage(), caepe::ActionResponse::SUCCESS);
    EXPECT_FALSE(actionResponse2.hasData());
    caepe::ActionResponse actionResponse3 { caepe::ActionResponse::FAILURE };
    EXPECT_EQ(actionResponse3.getMessage(), caepe::ActionResponse::FAILURE);
    EXPECT_FALSE(actionResponse3.hasData());
    caepe::ActionResponse actionResponse4 { "SampleMessage", 5 };
    EXPECT_EQ(actionResponse4.getMessage(), "SampleMessage");
    EXPECT_TRUE(actionResponse4.hasData());

}

TEST(ActionResponseTest, DefaultMessageTest)
{
    caepe::ActionResponse actionResponse;
    EXPECT_EQ(actionResponse.getMessage(), caepe::ActionResponse::UNDEFINED);
    EXPECT_FALSE(actionResponse.hasData());
}

TEST(ActionResponseTest, ActionResponseStoresCopyOfVectorOfStringsTest)
{
    std::vector<std::string> numbers = {"Test1", "Test2", "Test3"};
    caepe::ActionResponse actionResponse { caepe::ActionResponse::SUCCESS, numbers };
    EXPECT_EQ(actionResponse.getMessage(), caepe::ActionResponse::SUCCESS);
    ASSERT_TRUE(actionResponse.hasData());
    ASSERT_TRUE(actionResponse.getDataType() == typeid(std::vector<std::string>));
    std::vector<std::string> responseData;
    EXPECT_TRUE(actionResponse.getData<std::vector<std::string>>(responseData));
    ASSERT_GE(responseData.size(), 3);
    EXPECT_EQ(responseData.size(), 3);
    EXPECT_EQ(responseData[0], "Test1");
    EXPECT_EQ(responseData[1], "Test2");
    EXPECT_EQ(responseData[2], "Test3");
    numbers[0] = "ChangedTest1";
    EXPECT_EQ(numbers[0], "ChangedTest1");
    EXPECT_EQ(responseData[0], "Test1");
    EXPECT_NE(&responseData, &numbers);
}

TEST(ActionResponseTest, TryingToRetrieveDataInActionResponseWithNoDataTest)
{
    caepe::ActionResponse actionResponse;
    EXPECT_FALSE(actionResponse.hasData());

    EXPECT_EQ(actionResponse.getDataType(), typeid(void));

    int x = 101;
    EXPECT_FALSE(actionResponse.getData<int>(x));
    EXPECT_EQ(x, 101);
}