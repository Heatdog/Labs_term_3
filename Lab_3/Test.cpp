//
// Created by User on 26.09.2021.
//

#include <gtest/gtest.h>
#include "Prog3.h"

using namespace Prog3;

TEST(NumberTest, DefaultConstructor){
    Number number;
    char s[10];

    number.get_data(s, 9);
    EXPECT_STREQ(s, "0000000000");
}

TEST(NumberTest, Constructor){ // числа хранятся в обратном порядке!
    Number number(11);
    char s[10];

    number.get_data(s, 9);
    EXPECT_STREQ(s, "1101000000");

    Number number_1(-0);
    number_1.get_data(s, 9);
    EXPECT_STREQ(s, "0000000000");

    Number number_2(-21);
    number_2.get_data(s, 9);
    EXPECT_STREQ(s, "1010100001");

    Number number_3(43);
    number_3.get_data(s, 9);
    EXPECT_STREQ(s, "1101010000");

    Number number_s_1("58");
    number_s_1.get_data(s, 9);
    EXPECT_STREQ(s, "0101110000");

    Number number_s_2("0");
    number_s_2.get_data(s, 9);
    EXPECT_STREQ(s, "0000000000");

    Number number_s_3("-27");
    number_s_3.get_data(s, 9);
    EXPECT_STREQ(s, "1101100001");
}

TEST(NumberTest, DopCode){
    char s[10];

    Number number1(-12);
    number1.dop_code().get_data(s, 9);
    EXPECT_STREQ(s, "0010111111");

    Number number2(-0);
    number2.dop_code().get_data(s, 9);
    EXPECT_STREQ(s, "0000000000");

    Number number3(59);
    number3.dop_code().get_data(s, 9);
    EXPECT_STREQ(s, "1101110000");

    Number number4("-15");
    number4.dop_code().get_data(s, 9);
    EXPECT_STREQ(s, "1000111111");

    Number number5("-134");
    number5.dop_code().get_data(s, 9);
    EXPECT_STREQ(s, "0101111011");

    Number number6("48");
    number6.dop_code().get_data(s, 9);
    EXPECT_STREQ(s, "0000110000");
}

TEST(NumberTest, Sum){
    char s[10];

    Number number1_1(14), number1_2(27);
    sum(number1_1, number1_2).get_data(s, 9);
    EXPECT_STREQ(s, "1001010000");

    Number number2_1("4"), number2_2("8");
    sum(number2_1, number2_2).get_data(s, 9);
    EXPECT_STREQ(s, "0011000000");

    Number number3_1(-30), number3_2(-13);
    sum(number3_1, number3_2).get_data(s, 9);
    EXPECT_STREQ(s, "1101010001");

    Number number4_1("-10"), number4_2("-8");
    sum(number4_1, number4_2).get_data(s, 9);
    EXPECT_STREQ(s, "0100100001");

    Number number5_1(46), number5_2(-10);
    sum(number5_1, number5_2).get_data(s, 9);
    EXPECT_STREQ(s, "0010010000");

    Number number6_1("30"), number6_2("-24");
    sum(number6_1, number6_2).get_data(s, 9);
    EXPECT_STREQ(s, "0110000000");

    Number number7_1(14), number7_2(-30);
    sum(number7_1, number7_2).get_data(s, 9);
    EXPECT_STREQ(s, "0000100001");

    Number number8_1("6"), number8_2("-32");
    sum(number8_1, number8_2).get_data(s, 9);
    EXPECT_STREQ(s, "0101100001");

    Number number9_1(-0), number9_2(0);
    sum(number9_1, number9_2).get_data(s, 9);
    EXPECT_STREQ(s, "0000000000");
}

TEST(NumberTest, Prefix){
    char s[10];

    Number number1_1(4), number1_2(2);
    sum(number1_1.prefix(), number1_2).get_data(s, 9);
    EXPECT_STREQ(s, "1110000000");

    Number number2(-1);
    number2.prefix().get_data(s, 9);
    EXPECT_STREQ(s, "0000000000");

    Number number3("10");
    number3.prefix().get_data(s, 9);
    EXPECT_STREQ(s, "1101000000");
}

TEST(NumberTest, Postfix){
    char s[10];

    Number number1_1(4);
    for (int i = 0; i < 1; i++, number1_1.postfix_dec()){
        number1_1.get_data(s, 9);
        EXPECT_STREQ(s, "0010000000");
    }
    number1_1.get_data(s, 9);
    EXPECT_STREQ(s, "1100000000");

    Number number2_1(-6);
    for (int i = 0; i < 1; i++, number2_1.postfix_dec()){
        number2_1.get_data(s, 9);
        EXPECT_STREQ(s, "0110000001");
    }
    number2_1.get_data(s, 9);
    EXPECT_STREQ(s, "1110000001");

    Number number3_1("0");
    for (int i = 0; i < 1; i++, number3_1.postfix_dec()){
        number3_1.get_data(s, 9);
        EXPECT_STREQ(s, "0000000000");
    }
    number3_1.get_data(s, 9);
    EXPECT_STREQ(s, "1000000001");
}

TEST(NumberTest, Sign){
    char s[1];

    Number number(46);
    s[0] = number.sign();
    EXPECT_STREQ(s, "0");

    Number number1(-0);
    s[0] = number1.sign();
    EXPECT_STREQ(s, "0");

    Number number2(-12);
    s[0] = number2.sign();
    EXPECT_STREQ(s, "1");

    Number number3(0);
    s[0] = number3.sign();
    EXPECT_STREQ(s, "0");
}

TEST(NumberTest, Exception){
    EXPECT_THROW(Number number1(99999999999999999), std::out_of_range);
    EXPECT_THROW(Number number2("99999999999999999"), std::out_of_range);
    EXPECT_THROW(Number number3("abc"), std::invalid_argument);
    Number a(400), b(200);
    EXPECT_THROW(sum(a, b), std::out_of_range);


}

