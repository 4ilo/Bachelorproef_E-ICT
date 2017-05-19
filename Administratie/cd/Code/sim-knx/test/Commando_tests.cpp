//
// Created by olivier on 27/02/17.
//


#include "gtest/gtest.h"
#include "../sim-knx/inc/Commando.h"

class Commando_tests : ::testing::Test {
protected:

};

TEST(Commando_tests, commando_can_build_object_with_constructor)
{
    ASSERT_NO_THROW(Commando testCommando("test"));
}

TEST(Commando_tests, a_commando_can_be_send)
{
    // Capture cout
    testing::internal::CaptureStdout();

    // Create testCommando with no parameter and no data
    Commando testCommando("test");

    testCommando.send();

    // Save cout to string
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_STREQ(output.c_str(), "test\n\r");
}

TEST(Commando_tests, a_commando_can_accept_a_parameter)
{
    // Capture cout
    testing::internal::CaptureStdout();

    // Create testCommando with 1 parameter and no data
    Commando testCommando("test", 1);
    testCommando.setParameter(5);
    testCommando.send();

    // Save cout to string
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_STREQ(output.c_str(), "test (5 )\n\r");
}

TEST(Commando_tests, a_commando_throws_an_error_when_expecting_a_parameter)
{
    // Create testCommando with 1 parameter and no data
    //Commando testCommando("test", 1);
    //ASSERT_EXIT(testCommando.send(),1,"succes");
}

TEST(Commando_tests, a_commando_can_accept_multiple_parameters)
{
    // Capture cout
    testing::internal::CaptureStdout();

    // Create testCommando with 2 parameter and no data
    Commando testCommando("test", 2);
    testCommando.setParameter(5).setParameter(6);
    testCommando.send();

    // Save cout to string
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_STREQ(output.c_str(), "test (5 6 )\n\r");
}

TEST(Commando_tests, a_commando_can_accept_some_data_as_int)
{
    // Capture cout
    testing::internal::CaptureStdout();

    // Create testCommando with 0 parameter and 1 data
    Commando testCommando("test", 0, 1);
    testCommando.setData(5);
    testCommando.send();

    // Save cout to string
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_STREQ(output.c_str(), "test 5 \n\r");
}

TEST(Commando_tests, a_commando_can_accept_some_data_as_string)
{
    // Capture cout
    testing::internal::CaptureStdout();

    // Create testCommando with 0 parameter and 1 data
    Commando testCommando("test", 0, 1);
    testCommando.setData("1/2/3");
    testCommando.send();

    // Save cout to string
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_STREQ(output.c_str(), "test 1/2/3 \n\r");
}

TEST(Commando_tests, a_commando_can_accept_more_data)
{
    // Capture cout
    testing::internal::CaptureStdout();

    // Create testCommando with 0 parameter and 1 data
    Commando testCommando("test", 0, 2);
    testCommando.setData(5).setData("1/2/3");
    testCommando.send();

    // Save cout to string
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_STREQ(output.c_str(), "test 5 1/2/3 \n\r");
}

TEST(Commando_tests, a_commando_can_get_some_data_and_return_this_raw)
{
    // Capture cout
    testing::internal::CaptureStdout();

    Commando testCommando("test");
    string result = testCommando.get("$123").raw();

    // Save cout to string
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(result, "$123");
}