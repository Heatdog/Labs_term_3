// Created by User on 23.11.2021.
//

#include "gtest/gtest.h"
#include "UnordedNode.h"

using namespace Lab4;

TEST(STL_Test, MapTest){
    unordered_map<int, std::string> table;
    typedef std::pair<typename unordered_map<int, std::string>::iterator, bool> pair;
    pair t1 = table.emplace(std::make_pair(10, "aaa"));
    EXPECT_EQ((*t1.first).first, 10);
    EXPECT_EQ(t1.second, true);
    pair t2 = table.emplace(std::make_pair(12, "bbb"));
    EXPECT_EQ((*t2.first).first, 12);
    EXPECT_EQ(t2.second, true);
    pair t3 = table.emplace(std::make_pair(8, "ccc"));
    EXPECT_EQ((*t3.first).first, 8);
    EXPECT_EQ(t3.second, true);
    pair t4 = table.emplace(std::make_pair(1, "aaa"));
    EXPECT_EQ((*t4.first).first, 1);
    EXPECT_EQ(t4.second, true);
    pair t5 = table.emplace(std::make_pair(100, "aaa"));
    EXPECT_EQ((*t5.first).first, 100);
    EXPECT_EQ(t5.second, true);
    pair t6 = table.emplace(std::make_pair(90, "aaa"));
    EXPECT_EQ((*t6.first).first, 90);
    EXPECT_EQ(t6.second, true);
    pair t7 = table.emplace(std::make_pair(-8, "aaa"));
    EXPECT_EQ((*t7.first).first, -8);
    EXPECT_EQ(t7.second, true);
    EXPECT_EQ(table.size(), 7);
    pair t8 = table.emplace(std::make_pair(100, "aaa"));
    EXPECT_EQ((*t8.first).first, 100);
    EXPECT_EQ(t8.second, false);
    EXPECT_EQ(table.size(), 7);
    EXPECT_EQ(table.erase(10), 1);
    EXPECT_EQ(table.erase(-10), 0);
    EXPECT_EQ(table.erase(100), 1);
    EXPECT_EQ(table.erase(-8), 1);
    EXPECT_EQ(table.erase(-8), 0);
    EXPECT_EQ(table.size(), 4);

    pair t9 = table.emplace(std::make_pair(10, "aaa"));
    EXPECT_EQ(table.size(), 5);
    EXPECT_EQ(table.erase(10), 1);
    EXPECT_EQ(table.size(), 4);

}
