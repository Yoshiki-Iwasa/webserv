#include "./source/googletest-release-1.8.1/googletest/include/gtest/gtest.h"
#include "../sample.h"

// g++ -std=c++11 ../sample.cc sample_test.cc -o test -I ./source/googletest-release-1.8.1/googletest/include -L ./source/googletest-release-1.8.1/build/googlemock/gtest/ -pthread -lgtest -lgtest_main

TEST(IsEvenTest, Negative) {
    EXPECT_FALSE(IsEven(-1));
    EXPECT_TRUE(IsEven(-2));
}

TEST(IsEvenTest, Zero) {
    EXPECT_TRUE(IsEven(0));
}

TEST(IsEvenTest, Positive) {
    EXPECT_FALSE(IsEven(1));
    EXPECT_TRUE(IsEven(2));
}
