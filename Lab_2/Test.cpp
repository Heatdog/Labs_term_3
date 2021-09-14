//
// Created by User on 14.09.2021.
//

#include <gtest/gtest.h>
#include "Prog2.h"

using namespace Prog2;

TEST(LemniscataTest, DefaultConstructor){
    LemniscataButa line;
    EXPECT_EQ(0, line.get_c());
    EXPECT_EQ(0, line.get_m());
    EXPECT_EQ(0, line.get_polar_cos());
    EXPECT_EQ(0, line.get_polar_sin());
}

TEST(LemniscataTest, Constructor){
    LemniscataButa line(2, 3); // гиперболический
    EXPECT_EQ(2, line.get_c());
    EXPECT_EQ(3, line.get_m());
    EXPECT_EQ(20 ,line.get_polar_cos());
    EXPECT_EQ(-16 ,line.get_polar_sin());

    LemniscataButa line_1(10, 1); // эллиптический
    EXPECT_EQ(10, line_1.get_c());
    EXPECT_EQ(1, line_1.get_m());
    EXPECT_EQ(12 ,line_1.get_polar_cos());
    EXPECT_EQ(8 ,line_1.get_polar_sin());

    LemniscataButa line_2(2, 1); // 2 окружности
    EXPECT_EQ(2, line_2.get_c());
    EXPECT_EQ(1, line_2.get_m());
    EXPECT_EQ(-2 ,line_2.get_polar_cos());
    EXPECT_EQ(0 ,line_2.get_polar_sin());

    LemniscataButa line_3(0, 1); // лемнискат Бернулли
    EXPECT_EQ(0, line_3.get_c());
    EXPECT_EQ(1, line_3.get_m());
    EXPECT_EQ(2 ,line_3.get_polar_cos());
    EXPECT_EQ(0 ,line_3.get_polar_sin());
}

TEST(LemniscataTest, SetGet){
    LemniscataButa line(2, 3);
    EXPECT_EQ(line.get_c(), 2);
    EXPECT_EQ(line.get_m(), 3);

    line.set_c(5), line.set_m(-0.6);
    EXPECT_EQ(line.get_c(), 5);
    EXPECT_EQ(line.get_m(), -0.6);

    line.set_c(0);
    EXPECT_EQ(line.get_c(), 0);
    EXPECT_EQ(line.get_m(), -0.6);
}

TEST(LemniscataTest, Type){
    LemniscataButa line(2, 3); // гиперболический
    EXPECT_EQ(line.type(), "hyperbolic");

    LemniscataButa line_1(10, 1); // эллиптический
    EXPECT_EQ(line_1.type(), "elliptical");

    LemniscataButa line_2(2, 1); // 2 окружности
    EXPECT_EQ(line_2.type(), "two circle");

    LemniscataButa line_3(0, 1); // лемнискат Бернулли
    EXPECT_EQ(line_3.type(), "lemniscata bernoulli");
}

TEST(LemniscataTest, Area){
    LemniscataButa line(2, 3);
    EXPECT_NEAR(line.area(), 10.62641, 0.1);

    LemniscataButa line_1(10, 1);
    EXPECT_NEAR(line_1.area(), 31.4, 0.1);

    LemniscataButa line_2(2, 1);
    EXPECT_NEAR(line_2.area(), 3.14*2, 0.1);

    LemniscataButa line_3(0, 1);
    EXPECT_NEAR(line_3.area(), 2, 0.1);
}

TEST(LemniscataTest, Radius){
    LemniscataButa line(2, 3);
    EXPECT_NEAR(line.radius(30), 3.31, 0.1);

    LemniscataButa line_2(2, 3);
    EXPECT_NEAR(line_2.radius(60), 0, 0.1);

    LemniscataButa line_1(10, 1);
    EXPECT_NEAR(line_1.radius(60), 3, 0.1);

    LemniscataButa line_3(2, 1);
    EXPECT_NEAR(line_3.radius(60), 1, 0.1);

    LemniscataButa line_4(0, 1);
    EXPECT_NEAR(line_4.radius(30), 1, 0.1);
}
