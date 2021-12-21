//
// Created by User on 18.12.2021.
//

#ifndef LAB4_CONSOLE_H
#define LAB4_CONSOLE_H

#include "Mission.h"

enum Level{
    L_EASY,
    L_MEDIUM,
    L_HARD,
};

class App{
private:
    Level level; // уровень
    Mission mission; // миссия
    void buy_convoy() noexcept;
    void buy_weapon() noexcept;
    static void print_info_ship(ShipType type_) noexcept;
    static void print_info_weapon(WeaponName type_) noexcept;
    static WeaponName select_weapon() noexcept;
    static int enter_int() noexcept;
    void sell_convoy() noexcept;
    void sell_weapon() noexcept;
    void print_all_convoy() const noexcept;
    void displace(int x_, int y_) noexcept;
    void shoot() noexcept;
    void bot_turn() noexcept;
    void displace_bot(int x_, int y_, int velocity) noexcept;
public:
    explicit App() noexcept; // выбор уровня
    void buy() noexcept; // покупка кораблей и вооружения
    bool upload() noexcept; // загрузка груза
    void gameplay() noexcept; // геймплей
};

#endif //LAB4_CONSOLE_H
