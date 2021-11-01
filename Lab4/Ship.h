//
// Created by User on 31.10.2021.
//

#ifndef LAB4_SHIP_H
#define LAB4_SHIP_H

#include <vector>
#include <array>
#include <iostream>
#include <cmath>

enum WeaponName{
    UNDEFINED,
    BIG,
    MEDIUM,
    SMALL,
};

enum ShipType{
    UNDEFINEDSHIP,
    BATTLESHIP,
    TRANSPORT,
    BATTLETRANSPORT,
};

struct Capitan{
    Capitan() noexcept = default;
    explicit Capitan(std::string const &name_, std::string const &rang_) noexcept : name(name_), rang(rang_){}
    std::string name;
    std::string rang;
};

class Weapon{
public:
    Weapon() noexcept;
    explicit Weapon(WeaponName name_, int damage_, int rate_, double range_, int max_ammo_, int ammo_, int price_);
    int shoot() noexcept; // выстрелить

    // Геттеры-----------
    WeaponName get_name() const noexcept{
        return name;
    }
    double get_range() const noexcept{
        return range;
    }
    int get_damage() const noexcept{
        return damage;
    }
    int get_rate() const noexcept{
        return rate;
    }
    int get_max_ammo() const noexcept{
        return max_ammo;
    }
    int get_ammo() const noexcept{
        return ammo;
    }
    int get_price() const noexcept{
        return price;
    }
    //-------------------------------------------
private:
    WeaponName name; // наименование
    int damage; // урон
    int rate; // скорострельность
    double range; // дальность
    int max_ammo; // макс боекомплект
    int ammo; // текущий боекомплект
    int price; // цена
};

class Ship{
public:
    Ship() noexcept;
    explicit Ship(ShipType type_, std::string const &name, Capitan const &capitan_, double speed_, double max_speed_,
                  int hp, int max_hp_, int price);

    // Геттеры --------------
    ShipType get_type() const noexcept{
        return type;
    }
    std::string get_name() const noexcept{
        return name;
    }
    Capitan get_cap() const noexcept{
        return capitan;
    }
    double get_speed() const noexcept{
        return speed;
    }
    double get_max_speed() const noexcept{
        return max_speed;
    }
    int get_hp() const noexcept{
        return hp;
    }
    int get_max_hp() const noexcept{
        return max_hp;
    };
    int get_price() const noexcept{
        return price;
    }
    // ----------------

    //Сеттеры----------
    void set_name(ShipType type_) noexcept{
        type = type_;
    }
    void set_speed(double speed_);
    //-----------------

    void take_damage(int damage); // получить попадание
private:
    ShipType type; // тип корабля
    std::string name; // имя
    Capitan capitan; // капитан
    double speed; // скорость
    double max_speed; // скорость
    int hp; // хп
    int max_hp; // макс хп
    int price; // цена
    int static const max_price = 10000; // макс цена без вооружения
};



class TransportShip : public Ship{
public:
    TransportShip() noexcept;
    explicit TransportShip(std::string const &name, Capitan const &capitan_, double speed_, double max_speed_,
                           int hp_, int max_hp_, int price_, int weight_, int max_weight_);

    // Геттеры ---------------
    int get_weight() const noexcept{
        return weight;
    }
    int get_max_weight() const noexcept{
        return max_weight;
    }
    double get_ratio() const noexcept{
        return ratio;
    }
    //---------------------------

    void set_weight(int amount); // установить вес
    double new_max_speed(int weight_) noexcept; // определить макс скорость при выбранной нагрузке
    void set_ratio(double rat_);

private:
    int weight; // масса текущего груза
    int max_weight; // макс масса груза
    double ratio; // коэффициент скорости в зависимости от массы груза
};


class BattleShip : public Ship{
public:
    BattleShip() noexcept;
    explicit BattleShip(std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
                        int hp_, int max_hp_, int price_, std::array<Weapon, 4> const &weapons_);

    // Сеттеры
    void set_weapons(Weapon const &wp, int number){
        weapons.at(number-1) = wp;
    }
    //

    // Геттеры
    Weapon get_weapons(int number) const{
        return weapons.at(number-1);
    }
    std::array<Weapon, 4> get_wp() const{
        return weapons;
    }
    //

    void modify_weapon(int number, WeaponName weapon); // модифицировать вооружение
    Weapon info_weapon(int number) const; // информация об оружии в данном участке корабля
    int shoot(int x, int y) noexcept; // выстрел из всех орудий
private:
    std::array<Weapon, 4> weapons;
};


class BattleTransport : public TransportShip{
public:
    BattleTransport() noexcept;
    explicit BattleTransport(std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
    int hp_, int max_hp_, int price_, int weight_, int max_weight_, std::array<Weapon, 4> const &weapons_);

    //Сеттеры
    void set_weapons(Weapon const &wp, int number){
        weapons.at(number-1) = wp;
    }
    //

    // Геттеры
    Weapon get_weapons(int number) const{
        return weapons.at(number-1);
    }
    std::array<Weapon, 4> get_wp() const{
        return weapons;
    }
    //

    void modify_weapon(int number, WeaponName weapon); // модифицировать вооружение
    Weapon info_weapon(int number) const; // информация об оружии в данном участке корабля
    int shoot(int x, int y) noexcept; // выстрел из всех орудий
private:
    std::array<Weapon, 4> weapons;
};


std::vector<Weapon> set_weapon(); // запись возможного вооружения

namespace Battle{
    template <class T>
    void modify_weapon(T& ship, int number, WeaponName weapon);

    template <class T>
    Weapon info_weapon(T const &ship, int number);

    template <class T>
    int shoot(T &ship, int x, int y) noexcept;
}

#endif //LAB4_SHIP_H
