//
// Created by User on 14.09.2021.
//

#include <gtest/gtest.h>
#include "Prog2.h"

using namespace Prog2;

TEST(LemniscataTest, DefaultConstructor){
    LemniscataButa line;
    EXPECT_DOUBLE_EQ(0, line.get_c());
    EXPECT_DOUBLE_EQ(0, line.get_m());
    EXPECT_DOUBLE_EQ(0, line.get_polar_cos());
    EXPECT_DOUBLE_EQ(0, line.get_polar_sin());
}

TEST(LemniscataTest, Constructor){
    LemniscataButa line(2, 3); // гиперболический (несколько тестов для 1 типа)
    EXPECT_DOUBLE_EQ(2, line.get_c());
    EXPECT_DOUBLE_EQ(3, line.get_m());
    EXPECT_DOUBLE_EQ(20 ,line.get_polar_cos());
    EXPECT_DOUBLE_EQ(-16 ,line.get_polar_sin());

    LemniscataButa line_1_1(-2.8, 2.9);
    EXPECT_NEAR(-2.7999, line_1_1.get_c(), 0.0001);
    EXPECT_NEAR(2.8999, line_1_1.get_m(), 0.0001);
    EXPECT_NEAR(14.02 ,line_1_1.get_polar_cos(), 0.0001);
    EXPECT_NEAR(-19.62,line_1_1.get_polar_sin(), 0.0001);

    LemniscataButa line_1(10, 1); // эллиптический
    EXPECT_DOUBLE_EQ(10, line_1.get_c());
    EXPECT_DOUBLE_EQ(1, line_1.get_m());
    EXPECT_DOUBLE_EQ(12 ,line_1.get_polar_cos());
    EXPECT_DOUBLE_EQ(8 ,line_1.get_polar_sin());

    LemniscataButa line_2_1(101.28, -4.34);
    EXPECT_NEAR(101.28, line_2_1.get_c(), 0.0001);
    EXPECT_NEAR(-4.33999, line_2_1.get_m(), 0.0001);
    EXPECT_NEAR(138.9512 ,line_2_1.get_polar_cos(), 0.0001);
    EXPECT_NEAR(63.608800,line_2_1.get_polar_sin(), 0.0001);

    LemniscataButa line_2(2, 1); // 2 окружности
    EXPECT_DOUBLE_EQ(2, line_2.get_c());
    EXPECT_DOUBLE_EQ(1, line_2.get_m());
    EXPECT_DOUBLE_EQ(-2 ,line_2.get_polar_cos());
    EXPECT_DOUBLE_EQ(0 ,line_2.get_polar_sin());

    LemniscataButa line_3_1(8, 2);
    EXPECT_NEAR(8, line_3_1.get_c(), 0.0001);
    EXPECT_NEAR(2, line_3_1.get_m(), 0.0001);
    EXPECT_NEAR(-4 ,line_3_1.get_polar_cos(), 0.0001);
    EXPECT_NEAR(0 ,line_3_1.get_polar_sin(), 0.0001);

    LemniscataButa line_3(0, 1); // лемнискат Бернулли
    EXPECT_DOUBLE_EQ(0, line_3.get_c());
    EXPECT_DOUBLE_EQ(1, line_3.get_m());
    EXPECT_DOUBLE_EQ(2 ,line_3.get_polar_cos());
    EXPECT_DOUBLE_EQ(0 ,line_3.get_polar_sin());

    LemniscataButa line_4_1(0, -5.84);
    EXPECT_NEAR(0, line_4_1.get_c(), 0.0001);
    EXPECT_NEAR(-5.84, line_4_1.get_m(), 0.0001);
    EXPECT_NEAR(68.211199999999991 ,line_4_1.get_polar_cos(), 0.0001);
    EXPECT_NEAR(0 ,line_4_1.get_polar_sin(), 0.0001);

    LemniscataButa line_5_1(0, 0);
    EXPECT_NEAR(0, line_5_1.get_c(), 0.0001);
    EXPECT_NEAR(0, line_5_1.get_m(), 0.0001);
    EXPECT_NEAR(0 ,line_5_1.get_polar_cos(), 0.0001);
    EXPECT_NEAR(0 ,line_5_1.get_polar_sin(), 0.0001);
}

TEST(LemniscataTest, SetGet){
    LemniscataButa line(2, 3);
    EXPECT_DOUBLE_EQ(line.get_c(), 2);
    EXPECT_DOUBLE_EQ(line.get_m(), 3);

    line.set_c(5), line.set_m(-0.6);
    EXPECT_DOUBLE_EQ(line.get_c(), 5);
    EXPECT_DOUBLE_EQ(line.get_m(), -0.6);

    line.set_c(0);
    EXPECT_DOUBLE_EQ(line.get_c(), 0);
    EXPECT_DOUBLE_EQ(line.get_m(), -0.6);

    line.set_c(-48.2678), line.set_m(-235671.999);
    EXPECT_NEAR(line.get_c(), -48.2678, 0.0001);
    EXPECT_NEAR(line.get_m(), -235671.999, 0.0001);
}

TEST(LemniscataTest, Type){ // сравнение через нумерация в Type
    LemniscataButa line(2, 3); // гиперболический
    EXPECT_EQ(line.type(), 3);

    LemniscataButa line_1(10, 1); // эллиптический
    EXPECT_EQ(line_1.type(), 0);

    LemniscataButa line_2(2, 1); // 2 окружности
    EXPECT_EQ(line_2.type(), 1);

    LemniscataButa line_3(0, 1); // лемнискат Бернулли
    EXPECT_EQ(line_3.type(), 2);

    LemniscataButa line_4(0, 0);
    EXPECT_EQ(line_4.type(), 1);
}

TEST(LemniscataTest, Area){
    LemniscataButa line(2, 3);
    EXPECT_DOUBLE_EQ(line.area(), 10.626409251135019);

    LemniscataButa line_1_1(-2.8, 2.9);
    EXPECT_NEAR(line_1_1.area(), 6.327684, 0.0001);

    LemniscataButa line_1(10, 1);
    EXPECT_NEAR(line_1.area(), 31.415926535897931, 0.0001);

    LemniscataButa line_2_1(101.28, -4.34);
    EXPECT_NEAR(line_2_1.area(), 318.1805, 0.0001);

    LemniscataButa line_2(2, 1);
    EXPECT_DOUBLE_EQ(line_2.area(), 6.2831853071795862);

    LemniscataButa line_3_1(8, 2);
    EXPECT_NEAR(line_3_1.area(), 25.13274, 0.0001);

    LemniscataButa line_3(0, 1);
    EXPECT_DOUBLE_EQ(line_3.area(), 2);

    LemniscataButa line_4_1(0, -5.84);
    EXPECT_NEAR(line_4_1.area(), 68.21119, 0.0001);

    LemniscataButa line_4(0, 0);
    EXPECT_DOUBLE_EQ(line_4.area(), 0);
}

TEST(LemniscataTest, Radius){
    LemniscataButa line(2, 3);
    EXPECT_DOUBLE_EQ(line.radius(30), 3.3166247903554003);

    LemniscataButa line_2(2, 3);
    EXPECT_DOUBLE_EQ(line_2.radius(60), 0);

    LemniscataButa line_1(10, 1);
    EXPECT_DOUBLE_EQ(line_1.radius(60), 3);

    LemniscataButa line_3(2, 1);
    EXPECT_DOUBLE_EQ(line_3.radius(60), 1);

    LemniscataButa line_4(0, 1);
    EXPECT_DOUBLE_EQ(line_4.radius(30), 1);

    LemniscataButa line_5(0, 0);
    EXPECT_DOUBLE_EQ(line_5.radius(60), 0);

    LemniscataButa line_6(-5.2, -8.4);
    EXPECT_DOUBLE_EQ(line_6.radius(-25.8), 9.0805492539204469);

    LemniscataButa line_1_1(-2.8, 2.9);
    EXPECT_NEAR(line_1_1.radius(-128.9), 0, 0.0001);

    LemniscataButa line_2_1(101.28, -4.34);
    EXPECT_NEAR(line_1_1.radius(0), 3.74432, 0.0001);

    LemniscataButa line_3_1(8, 2);
    EXPECT_NEAR(line_3_1.radius(391), 3.4286, 0.0001);

    LemniscataButa line_4_1(0, -5.84);
    EXPECT_NEAR(line_2.radius(48.184), 0.059581, 0.0001);


}

TEST(LemniscataTest, String){ // тестирование строк
    int const len = 100;
    char s[len];

    LemniscataButa line(2, 3);
    line.get_in_polar(s, len);
    EXPECT_STREQ(s, "r^2 = 20.00*(cos(fi))^2 - 16.00*(sin(fi))^2");

    LemniscataButa line_1(10, 1);
    line_1.get_in_polar(s, len);
    EXPECT_STREQ(s, "r^2 = 12.00*(cos(fi))^2 + 8.00*(sin(fi))^2");

    LemniscataButa line_2(2, 1);
    line_2.get_in_polar(s, len);
    EXPECT_STREQ(s, "r^2 = -2.00*(cos(fi))^2");

    LemniscataButa line_3(0, 1);
    line_3.get_in_polar(s, len);
    EXPECT_STREQ(s, "r^2 = 2.00*(cos(fi))^2");

    LemniscataButa line_4(0, 0);
    line_4.get_in_polar(s, len);
    EXPECT_STREQ(s, "r^2 = 0");
}

TEST(LemniscataTest, Exception){
    int const len = 20;
    char s[len];
    LemniscataButa line(10000000, 4000000);
    EXPECT_THROW(line.get_in_polar(s, len), std::out_of_range);
}
