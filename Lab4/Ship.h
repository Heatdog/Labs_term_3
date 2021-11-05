//
// Created by User on 31.10.2021.
//

#ifndef LAB4_SHIP_H
#define LAB4_SHIP_H

#include <utility>
#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <memory>

enum WeaponName{
    UNDEFINED,
    BIG,
    MEDIUM,
    SMALL,
};

enum ShipType{
    UNDEFINEDSHIP,
    TRANSPORT,
    BATTLETRANSPORT,
    DESTROYER,
    LCRUISER,
    HCRUISER,
    BATTLESHIP,
};

struct Capitan{
    Capitan() noexcept = default;
    explicit Capitan(std::string name_, std::string rang_) noexcept : name(std::move(name_)), rang(std::move(rang_)){}
    Capitan(Capitan const &a) = default;
    Capitan& operator=(Capitan const &a);
    std::string name;
    std::string rang;
};

class Weapon{
public:
    Weapon() noexcept;
    explicit Weapon(WeaponName name_, int damage_, int rate_, double range_, int max_ammo_, int ammo_, int price_);
    Weapon(Weapon const &a) = default;
    Weapon& operator=(Weapon const &a);
    int shoot() noexcept; // выстрелить

    // ----------------- Геттеры-----------
    WeaponName get_name() const noexcept{return name;}
    double get_range() const noexcept{return range;}
    int get_damage() const noexcept{return damage;}
    int get_rate() const noexcept{return rate;}
    int get_max_ammo() const noexcept{return max_ammo;}
    int get_ammo() const noexcept{return ammo;}
    int get_price() const noexcept{return price;}
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
    explicit Ship(ShipType type_, std::string name, Capitan const &capitan_, double speed_, double max_speed_,
                  int hp, int max_hp_, int price);
    Ship(Ship const &a) = default;
    Ship& operator=(Ship const &a);

    // ------------ Геттеры --------------
    ShipType get_type() const noexcept{return type;}
    std::string get_name() const noexcept{return name;}
    Capitan get_cap() const noexcept{return capitan;}
    double get_speed() const noexcept{return speed;}
    double get_max_speed() const noexcept{return max_speed;}
    int get_hp() const noexcept{return hp;}
    int get_max_hp() const noexcept{return max_hp;};
    int get_price() const noexcept{return price;}
    // ----------------

    // ------------ Сеттеры----------
    void set_type(ShipType type_) noexcept{type = type_;}
    void set_speed(double speed_);
    void set_name(std::string const &name_) noexcept {name = name_;}
    //-----------------

    void take_damage(int damage); // получить попадание

    //-------- Виртуальные методы для переопределения -------------
    virtual int get_weight() const noexcept {return 0;}
    virtual int get_max_weight() const noexcept {return 0;}
    virtual double get_ratio() const noexcept {return 0;};
    virtual Weapon get_weapons(int number) const {return {};};
    virtual std::array<Weapon, 4> get_wp() const {return {};};
    //---------------------------------------------------------
private:
    ShipType type; // тип корабля
    std::string name; // имя
    Capitan capitan; // капитан
    double speed; // скорость
    double max_speed; // скорость
    int hp; // хп
    int max_hp; // макс хп
    int price; // цена
};


class TransportShip : public Ship{
public:
    TransportShip() noexcept;
    explicit TransportShip(std::string const &name, Capitan const &capitan_, double speed_, double max_speed_,
                           int hp_, int max_hp_, int price_, int weight_, int max_weight_);
    TransportShip(TransportShip const &a) = default;
    TransportShip& operator=(TransportShip const &a) = default;

    // ------------------ Геттеры ---------------
    int get_weight() const noexcept override{return weight;}
    int get_max_weight() const noexcept override{return max_weight;}
    double get_ratio() const noexcept override{return ratio;}
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
    explicit BattleShip(ShipType type, std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
                        int hp_, int max_hp_, int price_, std::array<Weapon, 4> weapons_);
    explicit BattleShip(ShipType type, std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
                        int hp_, int max_hp_, int price_);
    BattleShip(BattleShip const &a) = default;
    BattleShip& operator=(BattleShip const &a) = default;

    // --------- Сеттеры --------------------
    void set_weapons(Weapon const &wp, int number){weapons.at(number-1) = wp;}
    // -------------------------------------

    // ---------- Геттеры ----------------------
    Weapon get_weapons(int number) const override{return weapons.at(number-1);}
    std::array<Weapon, 4> get_wp() const override{return weapons;}
    // -----------------------------------------

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
                             int hp_, int max_hp_, int price_, int weight_, int max_weight_);
    explicit BattleTransport(std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
    int hp_, int max_hp_, int price_, int weight_, int max_weight_, std::array<Weapon, 4> weapons_);
    BattleTransport(BattleTransport const &a) = default;
    BattleTransport& operator=(BattleTransport const &a) = default;

    //-------------- Сеттеры -------------------
    void set_weapons(Weapon const &wp, int number){weapons.at(number-1) = wp;}
    // ---------------------------------------

    // ----------------- Геттеры -----------------
    Weapon get_weapons(int number) const override{return weapons.at(number-1);}
    std::array<Weapon, 4> get_wp() const override{return weapons;}
    // ---------------------------------------

    void modify_weapon(int number, WeaponName weapon); // модифицировать вооружение
    Weapon info_weapon(int number) const; // информация об оружии в данном участке корабля
    int shoot(int x, int y) noexcept; // выстрел из всех орудий
private:
    std::array<Weapon, 4> weapons;
};


// отвечает за магазин вооружения и корпусов ------------------------------
std::vector<Weapon> set_weapon(); // запись возможного вооружения
std::vector<std::shared_ptr<Ship>> set_ships();
//--------------------------------------------------------------------------

namespace Battle{
    template <class T>
    void modify_weapon(T& ship, int number, WeaponName weapon);

    template <class T>
    Weapon info_weapon(T const &ship, int number);

    template <class T>
    int shoot(T &ship, int x, int y) noexcept;
}

#endif //LAB4_SHIP_H
