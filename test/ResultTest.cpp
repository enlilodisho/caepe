//
// Created by Enlil on 7/15/2022.
//
#include <caepe/Result.h>

#include <gtest/gtest.h>

TEST(ResultTest, ResultConstructorCheck)
{
    caepe::Result r1(caepe::RESULT_OK);
    ASSERT_EQ(r1.getValue(), caepe::RESULT_OK);
    caepe::Result r2(caepe::RESULT_ERROR);
    ASSERT_EQ(r2.getValue(), caepe::RESULT_ERROR);
    caepe::Result r3(caepe::RESULT_OK, "msg");
    ASSERT_EQ(r1.getValue(), caepe::RESULT_OK);
    caepe::Result r4(caepe::RESULT_ERROR, "msg");
    ASSERT_EQ(r2.getValue(), caepe::RESULT_ERROR);
}

TEST(ResultTest, AppendingResultValueProperty)
{
    caepe::Result result(caepe::RESULT_OK);
    ASSERT_EQ(result.isSuccess(), true);
    caepe::Result result2(caepe::RESULT_OK);
    result += result2;
    ASSERT_EQ(result.getValue(), caepe::RESULT_OK);
    result += caepe::Result(caepe::RESULT_ERROR);
    ASSERT_EQ(result.getValue(), caepe::RESULT_ERROR);
    result += caepe::Result(caepe::RESULT_OK);
    ASSERT_EQ(result.getValue(), caepe::RESULT_ERROR);
    ASSERT_EQ(result.isSuccess(), false);
    ASSERT_EQ(result2.getValue(), caepe::RESULT_OK);
}

TEST(ResultTest, AppendingResultAddsMessageProperty)
{
    caepe::Result result(caepe::RESULT_OK, "Line 1");
    result += caepe::Result(caepe::RESULT_OK);
    result += caepe::Result(caepe::RESULT_ERROR, "Line 2");
    result += caepe::Result(caepe::RESULT_OK);
    ASSERT_EQ(result.getMessage(), "Line 1\nLine 2");
}