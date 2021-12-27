//
// Created by User on 22.12.2021.
//

#include "Console.h"

void App::bot_turn() noexcept {
    if (mission.count_pirates() != 0 && mission.count_convoy() != 0) {
        auto table = mission.get_pirate_table()->get_table();
        int x_convoy = mission.get_convoy_table()->get_table().begin()->second.coord.x;
        int y_convoy = mission.get_convoy_table()->get_table().begin()->second.coord.y;
        for (auto const &i: table) {
            if (abs((i.second.coord.x - x_convoy)) > abs((i.second.coord.y - y_convoy))) { // сравниваем разность координат по модулю
                if (i.second.coord.x - x_convoy >= 0) {
                    displace_bot(-1, 0, i.first);
                } else {
                    displace_bot(1, 0, i.first);
                }
            } else {
                if (i.second.coord.y - y_convoy >= 0) {
                    displace_bot(0, -1, i.first);
                } else {
                    displace_bot(0, 1, i.first);
                }
            }
            shoot_bot(i.first);
        }
    }
}


void App::displace_bot(int x_, int y_, unsigned long const &id) noexcept {
    auto table = mission.get_pirate_table();
    Element el = table->find_element(id);
    int velocity = static_cast<int>(el.ship->get_speed());
    table->push_new_coord(id, el.coord.x + x_ * velocity, el.coord.y + (y_ * velocity)/3);
    el.coord.x += x_ * velocity;
    el.coord.y += (y_ * velocity)/3;
    if (el.coord.x < 0){
        table->push_new_coord(id, 0, el.coord.y);
    }
    if (el.coord.x > Map::get_distance()-1){
        table->push_new_coord(id, Map::get_distance()-1, el.coord.y);
    }
    if (el.coord.y < 1){
        table->push_new_coord(id, el.coord.x, 1);
    }
    if (el.coord.y > Map::get_height()-1){
        table->push_new_coord(id, el.coord.x, Map::get_height()-2);
    }
    el.ship->sprite.setPosition(static_cast<float>(el.coord.x), static_cast<float>(el.coord.y));
}

void App::shoot_bot(const unsigned long &id) noexcept {
    std::random_device rd;
    std::mt19937 mersenne(rd());


    auto table = mission.get_convoy_table()->get_table();
    unsigned long count_convoy = mission.count_convoy();
    if (count_convoy == 0){
        return;
    }
    int target = static_cast<int>(mersenne() % count_convoy); // выбираем случайный корабль
    int count = 0;
    for (auto &i : table){
        if (target == count){
            mission.shoot_pirate(id, i.first);
            break;
        }
        count++;
    }
}

