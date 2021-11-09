//
// Created by User on 07.11.2021.
//

#include "Mission.h"
#include <gtest/gtest.h>

TEST(TableTest, InsertAndFind){
    Mission mission;
    EXPECT_EQ(mission.get_pirate_table()->count(), 5);

    std::shared_ptr<Ship>sp1 = mission.get_pirate_table()->find("pirate1");
    EXPECT_EQ(sp1->get_type(), DESTROYER);
    EXPECT_EQ(sp1->get_speed(), 30);
    EXPECT_EQ(sp1->get_max_speed(), 30);
    EXPECT_EQ(sp1->get_hp(), 1500);
    EXPECT_EQ(sp1->get_max_hp(), 1500);
    EXPECT_EQ(sp1->get_price(), 12000);
    std::array<Weapon, 4> data1 = sp1->get_wp();
    EXPECT_EQ(data1.at(0).get_name(), SMALL);
    EXPECT_EQ(data1.at(1).get_name(), SMALL);
    EXPECT_EQ(data1.at(2).get_name(), SMALL);
    EXPECT_EQ(data1.at(3).get_name(), SMALL);

    std::shared_ptr<Ship>sp2 = mission.get_pirate_table()->find("pirate2");
    EXPECT_EQ(sp2->get_type(), LCRUISER);
    EXPECT_EQ(sp2->get_speed(), 25);
    EXPECT_EQ(sp2->get_max_speed(), 25);
    EXPECT_EQ(sp2->get_hp(), 2500);
    EXPECT_EQ(sp2->get_max_hp(), 2500);
    EXPECT_EQ(sp2->get_price(), 26000);
    std::array<Weapon, 4> data2 = sp2->get_wp();
    EXPECT_EQ(data2.at(0).get_name(), SMALL);
    EXPECT_EQ(data2.at(1).get_name(), MEDIUM);
    EXPECT_EQ(data2.at(2).get_name(), MEDIUM);
    EXPECT_EQ(data2.at(3).get_name(), BIG);

    std::shared_ptr<Ship>sp3 = mission.get_pirate_table()->find("pirate5");
    EXPECT_EQ(sp3->get_type(), DESTROYER);
    EXPECT_EQ(sp3->get_speed(), 30);
    EXPECT_EQ(sp3->get_max_speed(), 30);
    EXPECT_EQ(sp3->get_hp(), 1500);
    EXPECT_EQ(sp3->get_max_hp(), 1500);
    EXPECT_EQ(sp3->get_price(), 12000);
    std::array<Weapon, 4> data3 = sp3->get_wp();
    EXPECT_EQ(data3.at(0).get_name(), SMALL);
    EXPECT_EQ(data3.at(1).get_name(), SMALL);
    EXPECT_EQ(data3.at(2).get_name(), SMALL);
    EXPECT_EQ(data3.at(3).get_name(), SMALL);
}

TEST(TableTest, EraseAndFind){
    Mission mission;
    std::string key = "pirate1";

    EXPECT_EQ(mission.get_pirate_table()->count(), 5);

    mission.get_pirate_table()->erase(key);
    EXPECT_THROW(mission.get_pirate_table()->find(key), std::invalid_argument);

    EXPECT_EQ(mission.get_pirate_table()->count(), 4);
    EXPECT_THROW( mission.get_pirate_table()->find("pirate6"), std::invalid_argument);

    EXPECT_EQ(mission.get_pirate_table()->find("pirate2")->get_type(), LCRUISER);
}

TEST(TableTest, PirateTest){
    Mission mission;
    EXPECT_EQ(mission.get_pirate("pirate4")->get_type(), BATTLESHIP);

    mission.insert_pirate(BATTLESHIP, "pirate6", MEDIUM, MEDIUM, MEDIUM, BIG);
    EXPECT_EQ(mission.get_pirate("pirate6")->get_type(), BATTLESHIP);

    EXPECT_THROW(mission.insert_pirate(BATTLESHIP, "pirate3", MEDIUM, MEDIUM, MEDIUM, BIG), std::invalid_argument);
    EXPECT_EQ(mission.get_pirate("pirate3")->get_type(), HCRUISER);

    mission.erase_pirate("pirate1");
    EXPECT_THROW(mission.get_pirate("pirate1"), std::invalid_argument);

    EXPECT_THROW(mission.erase_pirate("pirate9"), std::invalid_argument);
}

TEST(TableTest, ConvoyTest){
    Mission mission;
    mission.buy_convoy_transport("convoy1", 20);
    EXPECT_THROW(mission.buy_convoy_transport("convoy1", 30), std::invalid_argument);
    EXPECT_THROW(mission.buy_convoy_transport("convoy3", 300), std::invalid_argument);
    EXPECT_THROW(mission.buy_convoy_transport("convoy2", -20), std::invalid_argument);

    mission.buy_convoy_battle(LCRUISER, "battle1", MEDIUM, MEDIUM, SMALL, BIG);
    EXPECT_THROW(mission.buy_convoy_battle(LCRUISER, "battle1", MEDIUM, MEDIUM, SMALL, BIG), std::invalid_argument);

    mission.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 20);
    EXPECT_THROW(mission.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 20), std::invalid_argument);

    EXPECT_THROW(mission.buy_convoy_battle_transport("battle_convoy2", MEDIUM, MEDIUM, SMALL, BIG, 60), std::invalid_argument);
    EXPECT_THROW(mission.buy_convoy_battle_transport("battle_convoy3", MEDIUM, MEDIUM, SMALL, BIG, -20), std::invalid_argument);

    EXPECT_EQ(mission.get_convoy("convoy1")->get_type(), TRANSPORT);
    EXPECT_EQ(mission.get_convoy("battle1")->get_type(), LCRUISER);
    EXPECT_EQ(mission.get_convoy("battle_convoy1")->get_type(), BATTLETRANSPORT);
    EXPECT_THROW(mission.get_convoy("convoy4"), std::invalid_argument);
}

TEST(MissionTest, Methods){
    Mission mission;
    EXPECT_EQ( mission.count_convoy(), 0);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 0);

    mission.buy_convoy_transport("convoy1", 20);
    mission.buy_convoy_battle(LCRUISER, "battle1", MEDIUM, MEDIUM, SMALL, BIG);
    mission.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 20);

    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 54000);

    EXPECT_EQ( mission.count_convoy(), 3);
    EXPECT_EQ( mission.count_pirates(), 5);

    EXPECT_EQ(mission.get_convoy("convoy1")->get_type(), TRANSPORT);
    EXPECT_EQ(mission.get_pirate("pirate1")->get_type(), DESTROYER);
    EXPECT_EQ(mission.get_convoy("battle1")->get_type(), LCRUISER);
    EXPECT_EQ(mission.get_convoy("battle_convoy1")->get_type(), BATTLETRANSPORT);

    EXPECT_EQ(mission.get_convoy("battle1")->get_weapons(1).get_name(), MEDIUM);
    EXPECT_EQ(mission.get_convoy("battle1")->get_weapons(4).get_name(), BIG);

    mission.buy_weapon("battle1", SMALL, 4);
    EXPECT_EQ(mission.get_convoy("battle1")->get_weapons(4).get_name(), SMALL);

    EXPECT_THROW( mission.buy_weapon("battle1", SMALL, 7), std::out_of_range);

    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 46000);

    mission.sell_weapon("battle1", 4);
    EXPECT_EQ(mission.get_convoy("battle1")->get_weapons(4).get_name(), UNDEFINED);

    EXPECT_THROW( mission.sell_weapon("battle1", 7), std::invalid_argument);

    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 44000);

    mission.sell_convoy("convoy1");
    EXPECT_THROW(mission.get_convoy("convoy1"), std::invalid_argument);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 41000);
    EXPECT_THROW( mission.sell_convoy("convoy1"), std::invalid_argument);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 41000);
    EXPECT_EQ( mission.count_convoy(), 2);
}

TEST(MissionTest, PirateException){
    Mission mission;
    EXPECT_EQ( mission.count_pirates(), 5);

    EXPECT_THROW(mission.insert_pirate(HCRUISER, "pirate3", MEDIUM, MEDIUM, MEDIUM, MEDIUM), std::invalid_argument);
    EXPECT_EQ( mission.count_pirates(), 5);

    mission.insert_pirate(HCRUISER, "pirate6", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 6);
    mission.insert_pirate(HCRUISER, "pirate7", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 7);
    mission.insert_pirate(HCRUISER, "pirate8", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 8);
    mission.insert_pirate(HCRUISER, "pirate9", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 9);
    mission.insert_pirate(HCRUISER, "pirate10", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 10);

    EXPECT_THROW(mission.insert_pirate(HCRUISER, "pirate11", MEDIUM, MEDIUM, MEDIUM, MEDIUM), std::range_error);
    EXPECT_EQ( mission.count_pirates(), 10);

    EXPECT_THROW(mission.erase_pirate("pirate20"), std::invalid_argument);
    mission.erase_pirate("pirate7");

    EXPECT_EQ( mission.count_pirates(), 9);
    mission.insert_pirate(HCRUISER, "pirate11", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 10);
}




