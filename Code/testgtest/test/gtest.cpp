#include "gtest/gtest.h"

#include "../src/file.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(test_case_name, test_name)
{
    ASSERT_EQ(function_to_test(5),11);
}