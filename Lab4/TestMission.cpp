
// Created by User on 07.11.2021.
//

#include "Mission.h"
#include <gtest/gtest.h>

TEST(TableTest, InsertAndFind){
    Mission mission;
    EXPECT_EQ(mission.get_pirate_table()->count(), 5);

    std::shared_ptr<Ship>sp1 = mission.get_pirate_table()->find(1);
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

    std::shared_ptr<Ship>sp2 = mission.get_pirate_table()->find(2);
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

    std::shared_ptr<Ship>sp3 = mission.get_pirate_table()->find(5);
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

TEST(TableTest, PirateTest){
    Mission mission;

    unsigned long const key1 = mission.insert_pirate(BATTLESHIP, "pirate6", MEDIUM, MEDIUM, MEDIUM, BIG);
    EXPECT_EQ(mission.get_pirate(key1)->get_type(), BATTLESHIP);

    EXPECT_THROW(mission.erase_pirate(10000), std::invalid_argument);
}

TEST(TableTest, ConvoyTest){
    Mission mission;

    unsigned long const key1 = mission.buy_convoy_transport("convoy1", 20);
    EXPECT_THROW(mission.buy_convoy_transport("convoy3", 300), std::invalid_argument);

    unsigned long const key2 = mission.buy_convoy_battle(LCRUISER, "battle1", MEDIUM, MEDIUM, SMALL, BIG);

    unsigned long const key3 = mission.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 20);

    EXPECT_THROW(mission.buy_convoy_battle_transport("battle_convoy2", MEDIUM, MEDIUM, SMALL, BIG, 60), std::invalid_argument);
    EXPECT_THROW(mission.buy_convoy_battle_transport("battle_convoy3", MEDIUM, MEDIUM, SMALL, BIG, -20), std::invalid_argument);

    EXPECT_EQ(mission.get_convoy(key1)->get_type(), TRANSPORT);
    EXPECT_EQ(mission.get_convoy(key2)->get_type(), LCRUISER);
    EXPECT_EQ(mission.get_convoy(key3)->get_type(), BATTLETRANSPORT);
    EXPECT_THROW(mission.get_convoy(10), std::invalid_argument);
}

TEST(MissionTest, Methods){
    Mission mission;
    EXPECT_EQ( mission.count_convoy(), 0);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 0);

    unsigned long const key1 = mission.buy_convoy_transport("convoy1", 20);
    unsigned long const key2 = mission.buy_convoy_battle(LCRUISER, "battle1", MEDIUM, MEDIUM, SMALL, BIG);
    unsigned long const key3 = mission.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 20);

    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 54000);

    EXPECT_EQ( mission.count_convoy(), 3);
    EXPECT_EQ( mission.count_pirates(), 5);

    EXPECT_EQ(mission.get_convoy(key1)->get_type(), TRANSPORT);
    EXPECT_EQ(mission.get_convoy(key2)->get_type(), LCRUISER);
    EXPECT_EQ(mission.get_convoy(key3)->get_type(), BATTLETRANSPORT);

    EXPECT_EQ(mission.get_convoy(key2)->get_weapons(1).get_name(), MEDIUM);
    EXPECT_EQ(mission.get_convoy(key2)->get_weapons(4).get_name(), BIG);

    mission.buy_weapon(key2, SMALL, 4);
    EXPECT_EQ(mission.get_convoy(key2)->get_weapons(4).get_name(), SMALL);

    EXPECT_THROW( mission.buy_weapon(key2, SMALL, 7), std::out_of_range);

    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 46000);

    mission.sell_weapon(key2, 4);
    EXPECT_EQ(mission.get_convoy(key2)->get_weapons(4).get_name(), UNDEFINED);

    EXPECT_THROW( mission.sell_weapon(key2, 7), std::out_of_range);

    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 44000);

    mission.sell_convoy(key1);
    EXPECT_THROW(mission.get_convoy(key1), std::invalid_argument);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 41000);
    EXPECT_THROW( mission.sell_convoy(key1), std::invalid_argument);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 41000);
    EXPECT_EQ( mission.count_convoy(), 2);
}

TEST(MissionTest, PirateException){
    Mission mission;
    EXPECT_EQ( mission.count_pirates(), 5);


    unsigned long const key6 = mission.insert_pirate(HCRUISER, "pirate6", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 6);
    unsigned long const key7 = mission.insert_pirate(HCRUISER, "pirate7", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 7);
    unsigned long const key8 = mission.insert_pirate(HCRUISER, "pirate8", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 8);
    unsigned long const key9 = mission.insert_pirate(HCRUISER, "pirate9", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 9);
    unsigned long const key10 = mission.insert_pirate(HCRUISER, "pirate10", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 10);

    EXPECT_THROW(mission.insert_pirate(HCRUISER, "pirate11", MEDIUM, MEDIUM, MEDIUM, MEDIUM), std::range_error);
    EXPECT_EQ( mission.count_pirates(), 10);

    EXPECT_THROW(mission.erase_pirate(100), std::invalid_argument);
    mission.erase_pirate(key7);

    EXPECT_EQ( mission.count_pirates(), 9);
    mission.insert_pirate(HCRUISER, "pirate11", MEDIUM, MEDIUM, MEDIUM, MEDIUM);
    EXPECT_EQ( mission.count_pirates(), 10);
}

TEST(MissionTest, Economy){
    Mission mission;
    EXPECT_EQ(mission.count_convoy(), 0);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 0);

    mission.buy_convoy_transport("convoy1", 20);
    mission.buy_convoy_battle(LCRUISER, "battle1", MEDIUM, MEDIUM, SMALL, BIG);
    mission.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 20);

    EXPECT_EQ(mission.count_convoy(), 3);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 54000);

    mission.buy_convoy_transport("convoy2", 20);
    mission.buy_convoy_transport("convoy3", 20);
    mission.buy_convoy_transport("convoy4", 20);
    mission.buy_convoy_transport("convoy5", 20);
    mission.buy_convoy_transport("convoy6", 20);

    EXPECT_EQ(mission.count_convoy(), 8);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 69000);

    EXPECT_THROW(mission.buy_convoy_battle(BATTLESHIP, "battle2", BIG, BIG, SMALL, BIG), std::overflow_error);

    EXPECT_EQ(mission.count_convoy(), 8);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 69000);


    unsigned long const key7 = mission.buy_convoy_transport("convoy7", 20);
    EXPECT_EQ(mission.count_convoy(), 9);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 72000);

    mission.sell_convoy(key7);
    EXPECT_EQ(mission.count_convoy(), 8);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 69000);

    unsigned long const key3 = mission.buy_convoy_battle(HCRUISER, "battle3", UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED);
    EXPECT_EQ(mission.count_convoy(), 9);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 78000);

    unsigned long const key8 = mission.buy_convoy_transport("convoy8", 20);

    EXPECT_THROW(mission.buy_convoy_battle(HCRUISER, "battle4", UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED), std::range_error);
    mission.sell_convoy(key8);
    EXPECT_EQ(mission.count_convoy(), 9);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 78000);

    mission.buy_weapon(key3, BIG, 1);
    EXPECT_EQ(mission.count_convoy(), 9);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 88000);

    EXPECT_THROW(mission.buy_weapon(key3, BIG, 0), std::out_of_range);
    EXPECT_EQ(mission.count_convoy(), 9);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 88000);

    mission.buy_weapon(key3, BIG, 2);
    mission.buy_weapon(key3, SMALL, 3);
    EXPECT_EQ(mission.count_convoy(), 9);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 100000);

    EXPECT_THROW(mission.buy_weapon(key3, BIG, 4), std::overflow_error);
    EXPECT_EQ(mission.count_convoy(), 9);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 100000);

    mission.sell_weapon(key3, 2);
    EXPECT_EQ(mission.count_convoy(), 9);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 90000);

    mission.buy_weapon(key3, MEDIUM, 2);
    mission.buy_weapon(key3, MEDIUM, 4);
    EXPECT_EQ(mission.count_convoy(), 9);
    EXPECT_EQ(mission.get_money(), 100000);
    EXPECT_EQ(mission.get_spent_money(), 98000);
}

TEST(MissionTest, WeightTest){
    Mission mission;
    double eps = 0.00001;

    unsigned long const key1 = mission.buy_convoy_transport("convoy1", 100);
    unsigned long const key2 = mission.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 25);
    unsigned long const key3 = mission.buy_convoy_battle(LCRUISER, "battle1", MEDIUM, MEDIUM, SMALL, BIG);

    EXPECT_NEAR(mission.get_convoy(key1)->get_speed(), 15, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 12.5, eps);
    EXPECT_EQ(mission.get_weight(), 125);
    EXPECT_EQ(mission.get_weight_lost(), 0);

    mission.upload_weight(key1, 50);
    mission.upload_weight(key2, 5);

    EXPECT_NEAR(mission.get_convoy(key1)->get_speed(), 7.5, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 10, eps);
    EXPECT_EQ(mission.get_weight(), 180);
    EXPECT_EQ(mission.get_weight_lost(), 0);

    EXPECT_THROW(mission.upload_weight(key3, 10), std::invalid_argument);
    EXPECT_THROW(mission.upload_weight(key1, 60), std::invalid_argument);
    EXPECT_THROW(mission.upload_weight(key1, 30), std::invalid_argument);

    EXPECT_NEAR(mission.get_convoy(key1)->get_speed(), 7.5, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 10, eps);
    EXPECT_EQ(mission.get_weight(), 180);
    EXPECT_EQ(mission.get_weight_lost(), 0);

    EXPECT_THROW(mission.upload_weight(key1, 21), std::invalid_argument);

    EXPECT_NEAR(mission.get_convoy(key1)->get_speed(), 7.5, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 10, eps);
    EXPECT_EQ(mission.get_weight(), 180);
    EXPECT_EQ(mission.get_weight_lost(), 0);

    mission.erase_convoy(key1);
    EXPECT_THROW(mission.get_convoy(key1)->get_speed(), std::invalid_argument);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 10, eps);
    EXPECT_EQ(mission.get_weight(), 30);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    unsigned long const key4 = mission.buy_convoy_transport("convoy2", 50);

    EXPECT_NEAR(mission.get_convoy(key4)->get_speed(), 22.5, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 10, eps);
    EXPECT_EQ(mission.get_weight(), 80);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    EXPECT_THROW(mission.unload_weight(key4, 100), std::invalid_argument);
    mission.unload_weight(key4, 50);

    EXPECT_NEAR(mission.get_convoy(key4)->get_speed(), 30, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 10, eps);
    EXPECT_EQ(mission.get_weight(), 30);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    EXPECT_THROW(mission.unload_weight(key2, 100), std::invalid_argument);
    mission.unload_weight(key2, 30);

    EXPECT_NEAR(mission.get_convoy(key4)->get_speed(), 30, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 25, eps);
    EXPECT_EQ(mission.get_weight(), 0);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    mission.upload_weight(key4, 100);
    EXPECT_NEAR(mission.get_convoy(key4)->get_speed(), 15, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 25, eps);
    EXPECT_EQ(mission.get_weight(), 100);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    mission.unload_weight(key4, 20);
    EXPECT_NEAR(mission.get_convoy(key4)->get_speed(), 18, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 25, eps);
    EXPECT_EQ(mission.get_weight(), 80);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    mission.upload_weight(key2, 30);
    EXPECT_NEAR(mission.get_convoy(key4)->get_speed(), 18, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 10, eps);
    EXPECT_EQ(mission.get_weight(), 110);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    mission.unload_weight(key2, 20);
    EXPECT_NEAR(mission.get_convoy(key4)->get_speed(), 18, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 20, eps);
    EXPECT_EQ(mission.get_weight(), 90);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    mission.sell_convoy(key4);
    EXPECT_THROW(mission.get_convoy(key4)->get_speed(), std::invalid_argument);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 20, eps);
    EXPECT_EQ(mission.get_weight(), 10);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    mission.sell_convoy(key2);
    EXPECT_THROW(mission.get_convoy(key4)->get_speed(), std::invalid_argument);
    EXPECT_THROW(mission.get_convoy(key2)->get_speed(), std::invalid_argument);
    EXPECT_EQ(mission.get_weight(), 0);
    EXPECT_EQ(mission.get_weight_lost(), 150);

    EXPECT_EQ(mission.count_convoy(), 1);
}

TEST(MissionTest, AutTest){
    Mission mission; // мало военных к транспортным
    double eps = 0.00001;

    unsigned long const key1 = mission.buy_convoy_transport("convoy1", 100);
    unsigned long const key2 = mission.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 25);
    mission.buy_convoy_battle(LCRUISER, "battle1", MEDIUM, MEDIUM, SMALL, BIG);
    unsigned long const key3 = mission.buy_convoy_transport("convoy2", 50);
    unsigned long const key4 = mission.buy_convoy_transport("convoy3", 25);
    unsigned long const key5 = mission.buy_convoy_transport("convoy4", 0);

    EXPECT_EQ(mission.get_weight(), 200);
    EXPECT_EQ(mission.get_weight_lost(), 0);

    EXPECT_NEAR(mission.get_convoy(key1)->get_speed(), 15, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 12.5, eps);
    EXPECT_NEAR(mission.get_convoy(key3)->get_speed(), 22.5, eps);
    EXPECT_NEAR(mission.get_convoy(key4)->get_speed(), 26.25, eps);
    EXPECT_NEAR(mission.get_convoy(key5)->get_speed(), 30, eps);

    mission.upload_automatically();

    EXPECT_EQ(mission.get_weight(), 200);
    EXPECT_EQ(mission.get_weight_lost(), 0);

    EXPECT_NEAR(mission.get_convoy(key1)->get_speed(), 22.5, eps);
    EXPECT_NEAR(mission.get_convoy(key2)->get_speed(), 25, eps);
    EXPECT_NEAR(mission.get_convoy(key3)->get_speed(), 22.5, eps);
    EXPECT_NEAR(mission.get_convoy(key4)->get_speed(), 22.5, eps);
    EXPECT_NEAR(mission.get_convoy(key5)->get_speed(), 22.5, eps);


    Mission mission2; // только транспорт

    unsigned long const key11 =  mission2.buy_convoy_transport("convoy1", 0);
    unsigned long const key12 = mission2.buy_convoy_transport("convoy2", 0);
    unsigned long const key13 = mission2.buy_convoy_transport("convoy3", 25);
    unsigned long const key14 = mission2.buy_convoy_transport("convoy4", 0);

    EXPECT_EQ(mission2.get_weight(), 25);
    EXPECT_EQ(mission2.get_weight_lost(), 0);

    EXPECT_NEAR(mission2.get_convoy(key11)->get_speed(), 30, eps);
    EXPECT_NEAR(mission2.get_convoy(key12)->get_speed(), 30, eps);
    EXPECT_NEAR(mission2.get_convoy(key13)->get_speed(), 26.25, eps);
    EXPECT_NEAR(mission2.get_convoy(key14)->get_speed(), 30, eps);

    mission2.upload_automatically();

    EXPECT_EQ(mission2.get_weight(), 200);
    EXPECT_EQ(mission2.get_weight_lost(), 0);

    EXPECT_NEAR(mission2.get_convoy(key11)->get_speed(), 22.5, eps);
    EXPECT_NEAR(mission2.get_convoy(key12)->get_speed(), 22.5, eps);
    EXPECT_NEAR(mission2.get_convoy(key13)->get_speed(), 22.5, eps);
    EXPECT_NEAR(mission2.get_convoy(key14)->get_speed(), 22.5, eps);

    Mission mission3; // ошибочный вариант

    unsigned long const key21 = mission3.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 25);
    unsigned long const key22 = mission3.buy_convoy_battle_transport("battle_convoy2", MEDIUM, MEDIUM, SMALL, BIG, 10);
    unsigned long const key23 = mission3.buy_convoy_battle_transport("battle_convoy3", MEDIUM, MEDIUM, SMALL, BIG, 0);

    EXPECT_NEAR(mission3.get_convoy(key21)->get_speed(), 12.5, eps);
    EXPECT_NEAR(mission3.get_convoy(key22)->get_speed(), 20, eps);
    EXPECT_NEAR(mission3.get_convoy(key23)->get_speed(), 25, eps);

    EXPECT_THROW(mission3.upload_automatically(), std::invalid_argument);

    EXPECT_NEAR(mission3.get_convoy(key21)->get_speed(), 12.5, eps);
    EXPECT_NEAR(mission3.get_convoy(key22)->get_speed(), 20, eps);
    EXPECT_NEAR(mission3.get_convoy(key23)->get_speed(), 25, eps);

    Mission mission4; // мало транспортна к военным

    unsigned long const key31 = mission4.buy_convoy_transport("convoy1", 40);
    unsigned long const key32 = mission4.buy_convoy_battle_transport("battle_convoy1", MEDIUM, MEDIUM, SMALL, BIG, 25);
    unsigned long const key33 = mission4.buy_convoy_battle_transport("battle_convoy2", MEDIUM, MEDIUM, SMALL, BIG, 10);
    unsigned long const key34 = mission4.buy_convoy_battle_transport("battle_convoy3", MEDIUM, MEDIUM, SMALL, BIG, 0);

    EXPECT_NEAR(mission4.get_convoy(key31)->get_speed(), 24, eps);
    EXPECT_NEAR(mission4.get_convoy(key32)->get_speed(), 12.5, eps);
    EXPECT_NEAR(mission4.get_convoy(key33)->get_speed(), 20, eps);
    EXPECT_NEAR(mission4.get_convoy(key34)->get_speed(), 25, eps);

    EXPECT_EQ(mission4.get_weight(), 75);
    EXPECT_EQ(mission4.get_weight_lost(), 0);

    mission4.upload_automatically();

    EXPECT_EQ(mission4.get_weight(), 200);
    EXPECT_EQ(mission4.get_weight_lost(), 0);

    EXPECT_NEAR(mission4.get_convoy(key31)->get_speed(), 13.5, eps);
    EXPECT_NEAR(mission4.get_convoy(key32)->get_speed(), 10, eps);
    EXPECT_NEAR(mission4.get_convoy(key33)->get_speed(), 10, eps);
    EXPECT_NEAR(mission4.get_convoy(key34)->get_speed(), 10, eps);

    Mission mission5; // только военные

    unsigned long const key41 = mission5.buy_convoy_battle_transport("battle_convoy1", SMALL, SMALL, SMALL, SMALL, 25);
    unsigned long const key42 = mission5.buy_convoy_battle_transport("battle_convoy2", SMALL, SMALL, SMALL, SMALL, 10);
    unsigned long const key43 = mission5.buy_convoy_battle_transport("battle_convoy3", SMALL, SMALL, SMALL, SMALL, 0);
    unsigned long const key44 = mission5.buy_convoy_battle_transport("battle_convoy4", SMALL, SMALL, SMALL, SMALL, 25);
    unsigned long const key45 = mission5.buy_convoy_battle_transport("battle_convoy5", SMALL, SMALL, SMALL, SMALL, 10);

    EXPECT_NEAR(mission5.get_convoy(key41)->get_speed(), 12.5, eps);
    EXPECT_NEAR(mission5.get_convoy(key42)->get_speed(), 20, eps);
    EXPECT_NEAR(mission5.get_convoy(key43)->get_speed(), 25, eps);
    EXPECT_NEAR(mission5.get_convoy(key44)->get_speed(), 12.5, eps);
    EXPECT_NEAR(mission5.get_convoy(key45)->get_speed(), 20, eps);

    EXPECT_EQ(mission5.get_weight(), 70);
    EXPECT_EQ(mission5.get_weight_lost(), 0);

    mission5.upload_automatically();

    EXPECT_EQ(mission5.get_weight(), 200);
    EXPECT_EQ(mission5.get_weight_lost(), 0);

    EXPECT_NEAR(mission5.get_convoy(key41)->get_speed(), 5, eps);
    EXPECT_NEAR(mission5.get_convoy(key42)->get_speed(), 5, eps);
    EXPECT_NEAR(mission5.get_convoy(key43)->get_speed(), 5, eps);
    EXPECT_NEAR(mission5.get_convoy(key44)->get_speed(), 5, eps);
    EXPECT_NEAR(mission5.get_convoy(key45)->get_speed(), 5, eps);



}




