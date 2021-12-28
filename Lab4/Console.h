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

class Map_Window{
private:
    static int const height = 25;
    static int const distance = 40;
    std::string map[25][40];
public:
    static int get_height() noexcept{
        return height;
    }
    static int get_distance() noexcept{
        return distance;
    }
    explicit Map_Window() noexcept;

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};

class App{
private:
    Level level; // уровень
    static std::string print_info_weapon(WeaponName type_, std::string& wd) noexcept;
    static WeaponName select_weapon(sf::RenderWindow* window, int i) noexcept;
    static int enter_int() noexcept;
    void displace(int x_, int y_) noexcept;
    void shoot() noexcept;
    void bot_turn() noexcept;
    void displace_bot(int x_, int y_, unsigned long const &id) noexcept;
    void shoot_bot(unsigned long const &id) noexcept;
public:
    explicit App(Level level_) noexcept; // выбор уровня
    void buy(sf::RenderWindow* window) noexcept; // покупка кораблей и вооружения
    bool upload(sf::RenderWindow* window) noexcept; // загрузка груза
    void gameplay(sf::RenderWindow* window) noexcept; // геймплей
    Level get_level() const noexcept {return level;}
    Mission mission; // миссия
    void buy_convoy(sf::RenderWindow* window) noexcept;
    void buy_weapon(sf::RenderWindow* window) noexcept;
    void sell_convoy(sf::RenderWindow* window) noexcept;
    void sell_weapon(sf::RenderWindow* window) noexcept;
    void print_all_convoy(sf::RenderWindow* window) const noexcept;
    static std::string print_info_ship(ShipType type_, std::string& wd) noexcept;
};

#endif //LAB4_CONSOLE_H
