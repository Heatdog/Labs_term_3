//
// Created by User on 01.11.2021.
//

#include <gtest/gtest.h>
#include "Ship.h"

TEST(WeaponTest, Constructor){
    Weapon wp;
    double eps = 0.000001;
    EXPECT_EQ(wp.get_name(), UNDEFINED);
    EXPECT_EQ(wp.get_damage(), 0);
    EXPECT_EQ(wp.get_rate(), 0);
    EXPECT_NEAR(wp.get_range(), 0, eps);
    EXPECT_EQ(wp.get_max_ammo(), 0);
    EXPECT_EQ(wp.get_ammo(), 0);
    EXPECT_EQ(wp.get_price(), 0);

    Weapon wp1(BIG, 100, 1, 100, 10, 10, 10000);
    EXPECT_EQ(wp1.get_name(), BIG);
    EXPECT_EQ(wp1.get_damage(), 100);
    EXPECT_EQ(wp1.get_rate(), 1);
    EXPECT_NEAR(wp1.get_range(), 100, eps);
    EXPECT_EQ(wp1.get_max_ammo(), 10);
    EXPECT_EQ(wp1.get_ammo(), 10);
    EXPECT_EQ(wp1.get_price(), 10000);

    Weapon wp2(MEDIUM, 50, 2, 50, 30, 30, 4000);
    EXPECT_EQ(wp2.get_name(), MEDIUM);
    EXPECT_EQ(wp2.get_damage(), 50);
    EXPECT_EQ(wp2.get_rate(), 2);
    EXPECT_NEAR(wp2.get_range(), 50, eps);
    EXPECT_EQ(wp2.get_max_ammo(), 30);
    EXPECT_EQ(wp2.get_ammo(), 30);
    EXPECT_EQ(wp2.get_price(), 4000);

    Weapon wp3(SMALL, 10, 15, 10, 200, 200, 2000);
    EXPECT_EQ(wp3.get_name(), SMALL);
    EXPECT_EQ(wp3.get_damage(), 10);
    EXPECT_EQ(wp3.get_rate(), 15);
    EXPECT_NEAR(wp3.get_range(), 10, eps);
    EXPECT_EQ(wp3.get_max_ammo(), 200);
    EXPECT_EQ(wp3.get_ammo(), 200);
    EXPECT_EQ(wp3.get_price(), 2000);

    EXPECT_THROW(Weapon(SMALL, -2, 0, -200, 60, 20, 10), std::invalid_argument);
}

TEST(WeaponTest, Shoot){
    Weapon wp1(BIG, 100, 1, 100, 10, 10, 10000);
    EXPECT_EQ(wp1.shoot(), 100*1);
    EXPECT_EQ(wp1.get_ammo(), 9);

    Weapon wp2(MEDIUM, 50, 2, 50, 30, 30, 4000);
    EXPECT_EQ(wp2.shoot(), 50*2);
    EXPECT_EQ(wp2.get_ammo(), 28);

    Weapon wp3(SMALL, 10, 15, 10, 200, 200, 2000);
    EXPECT_EQ(wp3.shoot(), 10*15);
    EXPECT_EQ(wp3.get_ammo(), 200-15);
}

TEST(CaptianTest, Constructor){
    Capitan cap1;
    EXPECT_EQ(cap1.name, "");
    EXPECT_EQ(cap1.rang, "");

    Capitan cap2("John", "Admiral");
    EXPECT_EQ(cap2.name, "John");
    EXPECT_EQ(cap2.rang, "Admiral");
}

TEST(TransportTest, Constructor){
    TransportShip sp1;
    EXPECT_EQ(sp1.get_type(), TRANSPORT);
    EXPECT_EQ(sp1.get_name(), "");
    EXPECT_EQ(sp1.get_cap().name, "");
    EXPECT_EQ(sp1.get_cap().rang, "");
    EXPECT_EQ(sp1.get_speed(), 0);
    EXPECT_EQ(sp1.get_max_speed(), 0);
    EXPECT_EQ(sp1.get_hp(), 0);
    EXPECT_EQ(sp1.get_max_hp(), 0);
    EXPECT_EQ(sp1.get_price(), 0);
    EXPECT_EQ(sp1.get_weight(), 0);
    EXPECT_EQ(sp1.get_max_weight(), 0);

    Capitan cap2("John", "1");
    TransportShip sp2("Shp2", cap2, 20, 20, 1000, 1000, 50000, 0, 200);
    EXPECT_EQ(sp2.get_type(), TRANSPORT);
    EXPECT_EQ(sp2.get_name(), "Shp2");
    EXPECT_EQ(sp2.get_cap().name, "John");
    EXPECT_EQ(sp2.get_cap().rang, "1");
    EXPECT_EQ(sp2.get_speed(), 20);
    EXPECT_EQ(sp2.get_max_speed(), 20);
    EXPECT_EQ(sp2.get_hp(), 1000);
    EXPECT_EQ(sp2.get_max_hp(), 1000);
    EXPECT_EQ(sp2.get_price(), 50000);
    EXPECT_EQ(sp2.get_weight(), 0);
    EXPECT_EQ(sp2.get_max_weight(), 200);

    TransportShip sp3("Shp3", cap2, 20, 20, 1000, 1000, 50000, 100, 200);
    EXPECT_EQ(sp3.get_type(), TRANSPORT);
    EXPECT_EQ(sp3.get_name(), "Shp3");
    EXPECT_EQ(sp3.get_cap().name, "John");
    EXPECT_EQ(sp3.get_cap().rang, "1");
    EXPECT_EQ(sp3.get_speed(), 10);
    EXPECT_EQ(sp3.get_max_speed(), 20);
    EXPECT_EQ(sp3.get_hp(), 1000);
    EXPECT_EQ(sp3.get_max_hp(), 1000);
    EXPECT_EQ(sp3.get_price(), 50000);
    EXPECT_EQ(sp3.get_weight(), 100);
    EXPECT_EQ(sp3.get_max_weight(), 200);

    Capitan cap3("Rick", "2");
    TransportShip sp4("Shp4", cap3, 20, 20, 500, 500, 10000, 175, 200);
    EXPECT_EQ(sp4.get_type(), TRANSPORT);
    EXPECT_EQ(sp4.get_name(), "Shp4");
    EXPECT_EQ(sp4.get_cap().name, "Rick");
    EXPECT_EQ(sp4.get_cap().rang, "2");
    EXPECT_EQ(sp4.get_speed(), 2.5);
    EXPECT_EQ(sp4.get_max_speed(), 20);
    EXPECT_EQ(sp4.get_hp(), 500);
    EXPECT_EQ(sp4.get_max_hp(), 500);
    EXPECT_EQ(sp4.get_price(), 10000);
    EXPECT_EQ(sp4.get_weight(), 175);
    EXPECT_EQ(sp4.get_max_weight(), 200);

    EXPECT_THROW(TransportShip("Sh5", cap3, 20, 20, 500, 500, 1000, -5, -100), std::invalid_argument);
}

TEST(TransportTest, Methods){
    double eps = 0.000001;
    Capitan cap2("John", "1");
    TransportShip sp3("Shp3", cap2, 20, 20, 1000, 1000, 50000, 100, 200);

    Capitan cap3("Rick", "2");
    TransportShip sp4("Shp4", cap3, 20, 20, 500, 500, 10000, 175, 200);

    sp3.set_weight(150);
    EXPECT_EQ(sp3.get_speed(), 5);
    EXPECT_EQ(sp3.get_max_speed(), 20);
    EXPECT_EQ(sp3.get_weight(), 150);
    EXPECT_EQ(sp3.get_max_weight(), 200);

    EXPECT_NEAR(sp4.new_max_speed(50), 15, eps);
    EXPECT_NEAR(sp4.new_max_speed(0), 20, eps);

    sp3.take_damage(100);
    EXPECT_EQ(sp3.get_hp(), 900);
    EXPECT_EQ(sp3.get_max_hp(), 1000);

    sp4.take_damage(400);
    EXPECT_EQ(sp4.get_hp(), 100);
    EXPECT_EQ(sp4.get_max_hp(), 500);

    EXPECT_THROW(sp3.set_weight(210), std::invalid_argument);
}


TEST(BattleShipTest, Constructor){
    std::vector<Weapon> shop = set_weapon();

    BattleShip sp1;
    EXPECT_EQ(sp1.get_type(), BATTLESHIP);
    EXPECT_EQ(sp1.get_name(), "");
    EXPECT_EQ(sp1.get_cap().name, "");
    EXPECT_EQ(sp1.get_cap().rang, "");
    EXPECT_EQ(sp1.get_speed(), 0);
    EXPECT_EQ(sp1.get_max_speed(), 0);
    EXPECT_EQ(sp1.get_hp(), 0);
    EXPECT_EQ(sp1.get_max_hp(), 0);
    EXPECT_EQ(sp1.get_price(), 0);
    std::array<Weapon, 4> data = sp1.get_wp();
    EXPECT_EQ(data.at(0).get_name(), UNDEFINED);
    EXPECT_EQ(data.at(1).get_name(), UNDEFINED);
    EXPECT_EQ(data.at(2).get_name(), UNDEFINED);
    EXPECT_EQ(data.at(3).get_name(), UNDEFINED);

    Capitan cap2("John", "1");
    std::array<Weapon, 4> data2;
    data2.at(0) = shop.at(0);
    data2.at(1) = shop.at(0);
    data2.at(2) = shop.at(1);
    data2.at(3) = shop.at(2);
    BattleShip sp2("Shp2", cap2, 20, 20, 1000, 1000, 50000, data2);
    EXPECT_EQ(sp2.get_type(), BATTLESHIP);
    EXPECT_EQ(sp2.get_name(), "Shp2");
    EXPECT_EQ(sp2.get_cap().name, "John");
    EXPECT_EQ(sp2.get_cap().rang, "1");
    EXPECT_EQ(sp2.get_speed(), 20);
    EXPECT_EQ(sp2.get_max_speed(), 20);
    EXPECT_EQ(sp2.get_hp(), 1000);
    EXPECT_EQ(sp2.get_max_hp(), 1000);
    EXPECT_EQ(sp2.get_price(), 50000);
    std::array<Weapon, 4> data3 = sp2.get_wp();
    EXPECT_EQ(data3.at(0).get_name(), BIG);
    EXPECT_EQ(data3.at(1).get_name(), BIG);
    EXPECT_EQ(data3.at(2).get_name(), MEDIUM);
    EXPECT_EQ(data3.at(3).get_name(), SMALL);
}

TEST(BattleShipTest, Methods){
    std::vector<Weapon> shop = set_weapon();

    Capitan cap2("John", "1");
    std::array<Weapon, 4> data2;
    data2.at(0) = shop.at(0);
    data2.at(1) = shop.at(0);
    data2.at(2) = shop.at(1);
    data2.at(3) = shop.at(2);
    BattleShip sp2("Shp2", cap2, 20, 20, 1000, 1000, 50000, data2);
    sp2.modify_weapon(1, SMALL);
    sp2.modify_weapon(4, BIG);
    std::array<Weapon, 4> data3 = sp2.get_wp();
    EXPECT_EQ(data3.at(0).get_name(), SMALL);
    EXPECT_EQ(data3.at(1).get_name(), BIG);
    EXPECT_EQ(data3.at(2).get_name(), MEDIUM);
    EXPECT_EQ(data3.at(3).get_name(), BIG);

    Weapon wp = sp2.info_weapon(4);
    EXPECT_EQ(wp.get_name(), BIG);

    EXPECT_EQ(sp2.shoot(10, 10), data3.at(1).get_damage()*data3.at(1).get_rate() + data3.at(2).get_damage()*data3.at(2).get_rate()
    + data3.at(3).get_damage()*data3.at(3).get_rate());

    EXPECT_THROW(sp2.modify_weapon(6, BIG) ,std::invalid_argument);
}


TEST(BattleTransportTest, Constructor){
    std::vector<Weapon> shop = set_weapon();

    BattleTransport sp1;
    EXPECT_EQ(sp1.get_type(), BATTLETRANSPORT);
    EXPECT_EQ(sp1.get_name(), "");
    EXPECT_EQ(sp1.get_cap().name, "");
    EXPECT_EQ(sp1.get_cap().rang, "");
    EXPECT_EQ(sp1.get_speed(), 0);
    EXPECT_EQ(sp1.get_max_speed(), 0);
    EXPECT_EQ(sp1.get_hp(), 0);
    EXPECT_EQ(sp1.get_max_hp(), 0);
    EXPECT_EQ(sp1.get_price(), 0);
    std::array<Weapon, 4> data = sp1.get_wp();
    EXPECT_EQ(data.at(0).get_name(), UNDEFINED);
    EXPECT_EQ(data.at(1).get_name(), UNDEFINED);
    EXPECT_EQ(data.at(2).get_name(), UNDEFINED);
    EXPECT_EQ(data.at(3).get_name(), UNDEFINED);
    EXPECT_EQ(sp1.get_weight(), 0);
    EXPECT_EQ(sp1.get_max_weight(), 0);

    Capitan cap2("John", "1");
    std::array<Weapon, 4> data2;
    data2.at(0) = shop.at(0);
    data2.at(1) = shop.at(0);
    data2.at(2) = shop.at(1);
    data2.at(3) = shop.at(2);
    BattleTransport sp2("Shp2", cap2, 20, 20, 1000, 1000, 50000, 100, 200, data2);
    EXPECT_EQ(sp2.get_type(), BATTLETRANSPORT);
    EXPECT_EQ(sp2.get_name(), "Shp2");
    EXPECT_EQ(sp2.get_cap().name, "John");
    EXPECT_EQ(sp2.get_cap().rang, "1");
    EXPECT_EQ(sp2.get_speed(), 10);
    EXPECT_EQ(sp2.get_max_speed(), 20);
    EXPECT_EQ(sp2.get_hp(), 1000);
    EXPECT_EQ(sp2.get_max_hp(), 1000);
    EXPECT_EQ(sp2.get_price(), 50000);
    std::array<Weapon, 4> data3 = sp2.get_wp();
    EXPECT_EQ(data3.at(0).get_name(), BIG);
    EXPECT_EQ(data3.at(1).get_name(), BIG);
    EXPECT_EQ(data3.at(2).get_name(), MEDIUM);
    EXPECT_EQ(data3.at(3).get_name(), SMALL);
    EXPECT_EQ(sp2.get_weight(), 100);
    EXPECT_EQ(sp2.get_max_weight(), 200);
}


TEST(BattleTransportTest, Methods){
    double eps = 0.000001;
    std::vector<Weapon> shop = set_weapon();
    Capitan cap2("John", "1");
    std::array<Weapon, 4> data2;
    data2.at(0) = shop.at(0);
    data2.at(1) = shop.at(0);
    data2.at(2) = shop.at(1);
    data2.at(3) = shop.at(2);
    BattleTransport sp2("Shp3", cap2, 20, 20, 1000, 1000, 50000, 100, 200, data2);

    Capitan cap3("Rick", "2");
    BattleTransport sp4("Shp4", cap3, 20, 20, 500, 500, 10000, 175, 200, data2);

    sp2.set_weight(150);
    EXPECT_EQ(sp2.get_speed(), 5);
    EXPECT_EQ(sp2.get_max_speed(), 20);
    EXPECT_EQ(sp2.get_weight(), 150);
    EXPECT_EQ(sp2.get_max_weight(), 200);

    EXPECT_NEAR(sp4.new_max_speed(50), 15, eps);
    EXPECT_NEAR(sp4.new_max_speed(0), 20, eps);

    sp2.take_damage(100);
    EXPECT_EQ(sp2.get_hp(), 900);
    EXPECT_EQ(sp2.get_max_hp(), 1000);

    sp4.take_damage(400);
    EXPECT_EQ(sp4.get_hp(), 100);
    EXPECT_EQ(sp4.get_max_hp(), 500);

    EXPECT_THROW(sp2.set_weight(210), std::invalid_argument);
}





