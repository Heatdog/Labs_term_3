//
// Created by User on 12.10.2021.
//

#include "Prog3.h"
#include <gtest/gtest.h>

using namespace Dynamic;



TEST(NumberTest, DefaultConstructor){
    Number number;
    std::string s;

    EXPECT_EQ(number.output(s), "00");
}

TEST(NumberTest, Constructor){
    std::string s;

    Number number(11);
    EXPECT_EQ(number.output(s), "01011");

    Number number_1(-0);
    EXPECT_EQ(number_1.output(s), "00");

    Number number_2(-21);
    EXPECT_EQ(number_2.output(s), "110101");

    Number number_3(43);
    EXPECT_EQ(number_3.output(s), "0101011");

    Number number_s_1("58");
    EXPECT_EQ(number_s_1.output(s), "0111010");

    Number number_s_2("0");
    EXPECT_EQ(number_s_2.output(s), "00");

    Number number_s_3("-27");
    EXPECT_EQ(number_s_3.output(s), "111011");

    Number number1(511);
    EXPECT_EQ(number1.output(s), "0111111111");

    Number number2(-511);
    EXPECT_EQ(number2.output(s), "1111111111");

    EXPECT_THROW(Number number3("abc"), std::invalid_argument);
}

TEST(NumberTest, DopCode){
    std::string s;

    Number number1(-12);
    EXPECT_EQ(number1.dop_code().output(s), "10100");

    Number number2(-0);
    EXPECT_EQ(number2.dop_code().output(s), "00");

    Number number3(59);
    EXPECT_EQ(number3.dop_code().output(s), "0111011");

    Number number4("-15");
    EXPECT_EQ(number4.dop_code().output(s), "10001");

    Number number5("-134");
    EXPECT_EQ(number5.dop_code().output(s), "101111010");

    Number number6("48");
    EXPECT_EQ(number6.dop_code().output(s), "0110000");

    Number number7("511");
    EXPECT_EQ(number7.dop_code().output(s), "0111111111");

    Number number8(-512);
    EXPECT_EQ(number8.dop_code().output(s), "11000000000");
}

TEST(NumberTest, Overload){
    std::string result;

    Number num1("110");
    Number num2;
    num2 = num1;
    EXPECT_EQ("01101110", num2.output(result));

    Number num3(59);
    Number num4;
    num4 = num3;
    EXPECT_EQ("0111011", num4.output(result));

    Number num5(-78);
    Number num6;
    num6 = num5;
    EXPECT_EQ("11001110", num6.output(result));

    Number num7(0);
    Number num8;
    num8 = num7;
    EXPECT_EQ("00", num8.output(result));

    std::string s1;
    Number num9(5);
    Number num10 = Number(3) + Number(2);
    EXPECT_EQ(num9.output(s1), num10.output(result));

    Number num11(120);
    Number num12 = Number(110) + Number(10);
    EXPECT_EQ(num11.output(s1), num12.output(result));

    Number num13(120);
    Number num14 = Number(140) + Number(-20);
    EXPECT_EQ(num13.output(s1), num14.output(result));
}

TEST(NumberTest, Move){
    std::string result;

    Number num1(110);
    Number num2;
    num2 = std::move(num1);
    EXPECT_EQ("01101110", num2.output(result));
    EXPECT_EQ("", num1.output(result));

    Number num3(59);
    Number num4;
    num4 = std::move(num3);
    EXPECT_EQ("0111011", num4.output(result));
    EXPECT_EQ("", num3.output(result));

    Number num5(-78);
    Number num6;
    num6 = std::move(num5);
    EXPECT_EQ("11001110", num6.output(result));
    EXPECT_EQ("", num5.output(result));

    Number num7(0);
    Number num8;
    num8 = std::move(num7);
    EXPECT_EQ("00", num8.output(result));
    EXPECT_EQ("", num7.output(result));
}

TEST(NumberTest, OverloadSum){
    std::string s;

    Number number1_1(14), number1_2(27);
    EXPECT_EQ((number1_1 + number1_2).output(s), "0101001");

    Number number2_1("4"), number2_2("8");
    EXPECT_EQ((number2_1 + number2_2).output(s), "01100");

    Number number3_1(-30), number3_2(-13);
    EXPECT_EQ((number3_1 + number3_2).output(s), "1101011");

    Number number4_1("-10"), number4_2("-8");
    EXPECT_EQ((number4_1 + number4_2).output(s), "110010");

    Number number5_1(46), number5_2(-10);
    EXPECT_EQ((number5_1 + number5_2).output(s), "0100100");

    Number number6_1("30"), number6_2("-24");
    EXPECT_EQ((number6_1 + number6_2).output(s), "0110");

    Number number7_1(14), number7_2(-30);
    EXPECT_EQ((number7_1 + number7_2).output(s), "110000");

    Number number8_1("6"), number8_2("-32");
    EXPECT_EQ((number8_1 + number8_2).output(s), "111010");

    Number number9_1(-0), number9_2(1);
    EXPECT_EQ((number9_1 + number9_2).output(s), "01");

    Number number10_1(11), number10_2(-10);
    EXPECT_EQ((number10_1 + number10_2).output(s), "01");

    std::string s1;
    Number number11(-120);
    EXPECT_EQ((Number(20) + Number(-140)).output(s), number11.output(s1));
}

TEST(NumberTest, OverloadSum_2){
    std::string s;

    Number number1_1(14), number1_2(27);
    EXPECT_EQ((number1_1 += number1_2).output(s), "0101001");

    Number number2_1("4"), number2_2("8");
    EXPECT_EQ((number2_1 += number2_2).output(s), "01100");

    Number number3_1(-30), number3_2(-13);
    EXPECT_EQ((number3_1 += number3_2).output(s), "1101011");

    Number number4_1("-10"), number4_2("-8");
    EXPECT_EQ((number4_1 += number4_2).output(s), "110010");

    Number number5_1(46), number5_2(-10);
    EXPECT_EQ((number5_1 += number5_2).output(s), "0100100");

    Number number6_1("30"), number6_2("-24");
    EXPECT_EQ((number6_1 += number6_2).output(s), "0110");

    Number number7_1(14), number7_2(-30);
    EXPECT_EQ((number7_1 += number7_2).output(s), "110000");

    Number number8_1("6"), number8_2("-32");
    EXPECT_EQ((number8_1 += number8_2).output(s), "111010");

    Number number9_1(-0), number9_2(1);
    EXPECT_EQ((number9_1 += number9_2).output(s), "01");

    Number number10_1(11), number10_2(-10);
    EXPECT_EQ((number10_1 += number10_2).output(s), "01");

    Number number11(10);
    EXPECT_EQ((number11 += number11).output(s), "010100");

    Number number12(-35);
    EXPECT_EQ((number12 += number12).output(s), "11000110");

    Number number13("47000001"), number13_1("-47000000");
    EXPECT_EQ((number13 += number13_1).output(s), "01");

    Number number14(47000001), number14_1(-47000000);
    EXPECT_EQ((number14 += number14_1).output(s), "01");
}

TEST(NumberTest, OverloadPostfix){
    std::string s;

    Number number1_1(4);
    EXPECT_EQ(number1_1.output(s), "0100");
    number1_1--;
    EXPECT_EQ(number1_1.output(s), "011");

    Number number2_1(-6);
    EXPECT_EQ(number2_1.output(s), "1110");
    EXPECT_EQ((number2_1--).output(s), "1110");

    Number number3_1("0");
    EXPECT_EQ(number3_1.output(s), "00");
    EXPECT_EQ((number3_1--).output(s), "00");

    Number number4_1("400");
    EXPECT_EQ(number4_1.output(s), "0110010000");
    number4_1--;
    EXPECT_EQ(number4_1.output(s), "0110001111");
}

TEST(NumberTest, OverloadIsstream){
    Number num;
    std::string result;
    std::istringstream is("112");
    std::ostringstream os;
    is >> num;
    EXPECT_EQ(num.output(result), "01110000");
    os << num;
    std::string s = os.str();
    EXPECT_EQ("01110000\n", s);

    Number num1(112);
    std::istringstream is1("abc");
    is1 >> num1;
    EXPECT_TRUE(is1.fail());

    Number num2;
    std::istringstream is2("-432");
    std::ostringstream os2;
    is2 >> num2;
    EXPECT_EQ(num2.output(result), "1110110000");
    os2 << num2;
    EXPECT_EQ("1110110000\n", os2.str());

    Number num3;
    std::istringstream is3("999999999999999999999");
    is3 >> num3;
    EXPECT_TRUE(is3.fail());
}

TEST(NumberTest, OverloadPrefix){
    std::string s;

    Number number1_1(4), number1_2(2);
    EXPECT_EQ((++number1_1 + number1_2).output(s), "0111");

    Number number2(-1);
    EXPECT_EQ((++number2).output(s), "00");

    Number number3("10");
    EXPECT_EQ((++number3).output(s), "01011");
}


