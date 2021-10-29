//
// Created by User on 29.10.2021.
//

#include <gtest/gtest.h>
#include "Dialog.h"

TEST(VectorTest, Orthogonality){
    std::vector<int> mass;
    int result[100];
    Prog3::Vector vec1("0x10x1"), vec2("010x10");
    result[0] = 3, result[1] = 6;
    mass = orthogonality(vec1, vec2);
    for (int i = 0; i < mass.size(); i++){
        EXPECT_EQ(result[i], mass.at(i));
    }

    Prog3::Vector vec3("011xx01"), vec4("1011x01");
    result[0] = 1, result[1] = 2;
    mass = orthogonality(vec3, vec4);
    for (int i = 0; i < mass.size(); i++){
        EXPECT_EQ(result[i], mass.at(i));
    }
}

TEST(VectorTest, Neighbor){
    int result;
    Prog3::Vector vec1("0x10x1"), vec2("0x10x0");
    result = neighbor(vec1, vec2);
    EXPECT_EQ(result, 6);

    Prog3::Vector vec3("1111x01"), vec4("1011x01");
    result = neighbor(vec3, vec4);
    EXPECT_EQ(result, 2);
}

TEST(VectorTest, Merger){
    bool result;
    Prog3::Vector vec1("0x10xx"), vec2("0x10x0");
    result = merger(vec1, vec2);
    EXPECT_EQ(result, true);

    Prog3::Vector vec3("111xx01"), vec4("1011x01");
    result = merger(vec3, vec4);
    EXPECT_EQ(result, false);
}


