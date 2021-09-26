//
// Created by User on 26.09.2021.
//

#include <gtest/gtest.h>
#include "Prog3.h"

using namespace Prog3;

TEST(NumberTest, DefaultConstructor){
    Number number;
    char s[20];

    number.get_data(s, 19);
    EXPECT_STREQ(s, "00000000000000000000");
}

