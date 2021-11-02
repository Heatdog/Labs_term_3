//
// Created by User on 31.10.2021.
//

#include "Ship.h"

// ----------- Капитан ----------------------

Capitan &Capitan::operator=(const Capitan &a) {
    if (this != &a){
        name.clear();
        rang.clear();
        name = a.name;
        rang = a.rang;
    }
    return *this;
}

// ----------- Вооружение --------------------

Weapon::Weapon() noexcept : name(UNDEFINED), damage(0), rate(0), range(0), max_ammo(0), ammo(0), price(0) {}

Weapon::Weapon(WeaponName name_, int damage_, int rate_, double range_, int max_ammo_, int ammo_, int price_)
    :name(name_), damage(damage_), rate(rate_), range(range_), max_ammo(max_ammo_), ammo(ammo_), price(price_){
    if (damage <= 0 || rate <= 0 || range <= 0 || max_ammo <= 0 || ammo <= 0 || price <= 0){
        throw std::invalid_argument("Invalid arg!");
    }
}

Weapon &Weapon::operator=(const Weapon &a) {
    if (this != &a){
        name = a.name;
        damage = a.damage;
        rate = a.rate;
        range = a.range;
        max_ammo = a.max_ammo;
        ammo = a.ammo;
        price = a.price;
    }
    return *this;
}

// выстрелить -----------------
int Weapon::shoot() noexcept {
    if (ammo == 0){
        return 0;
    }
    ammo -= rate;
    return damage*rate;
}

// ---------------- Корабль (базовый класс для всего остального) -------------------------

Ship::Ship() noexcept : type(UNDEFINEDSHIP), capitan(Capitan()), speed(0), max_speed(0), hp(0),
    max_hp(0), price(0){}


Ship::Ship(ShipType type_, std::string const &name, Capitan const &capitan_, double speed_, double max_speed_, int hp_, int max_hp_,
    int price_) : type(type_), name(name), capitan(capitan_), speed(speed_), max_speed(max_speed_),
    hp(hp_), max_hp(max_hp_), price(price_){
    if (speed <= 0 || max_speed <= 0 || hp <= 0 || max_hp_ <= 0){
        throw std::invalid_argument("Invalid arg!");
    }
}

Ship &Ship::operator=(const Ship &a) {
    if (this != &a){
        type = a.type;
        name.clear();
        name = a.name;
        capitan = a.capitan;
        speed = a.speed;
        max_speed = a.max_speed;
        hp = a.hp;
        max_hp = a.max_hp;
        price = a.price;
    }
    return *this;
}

// получить попадание -------------------
void Ship::take_damage(int damage) {
    hp -= damage;
    if (hp <= 0){} // работа с таблицей
}

void Ship::set_speed(double speed_) {
    if (speed_ < 0){
        throw std::invalid_argument("Invalid arg!");
    }
    speed = speed_;
}

// ---------------------- Транспортный корабль -----------------------

TransportShip::TransportShip() noexcept : Ship(), weight(0), max_weight(0), ratio(1) {
    set_name(TRANSPORT);
}

TransportShip::TransportShip(std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
     int hp_, int max_hp_, int price_, int weight_, int max_weight_)
     : Ship(TRANSPORT, name_, capitan_, speed_, max_speed_, hp_, max_hp_, price_)
     , weight(weight_), max_weight(max_weight_), ratio(1) {
    if (weight < 0 || max_weight < 0){
        throw std::invalid_argument("Invalid arg!");
    }
    set_weight(weight);
}

// установить вес ------------------------
void TransportShip::set_weight(int amount) {
    if (amount > max_weight){
        throw std::invalid_argument("Weight is too big!");
    }
    double rat = 1-static_cast<double >(amount)/static_cast<double >(max_weight);
    double new_speed = get_max_speed()*rat;
    set_ratio(rat);
    set_speed(new_speed);
    weight = amount;
}

// определить макс скорость при выбранной нагрузке -----------------
double TransportShip::new_max_speed(int weight_) noexcept {
    return get_max_speed()*(1-static_cast<double >(weight_)/static_cast<double >(max_weight));
}

void TransportShip::set_ratio(double rat_) {
    if (rat_ < 0 || rat_ > 1){
        throw std::invalid_argument("Rat can`t be that!");
    }
    ratio = rat_;
}

// --------------------- Военный корабль -------------------

BattleShip::BattleShip() noexcept : Ship() {
    set_name(BATTLESHIP);
}

BattleShip::BattleShip(ShipType type, const std::string &name_, const Capitan &capitan_, double speed_, double max_speed_,
     int hp_, int max_hp_, int price_, const std::array<Weapon, 4> &weapons_)
     : Ship(type, name_, capitan_, speed_, max_speed_, hp_, max_hp_, price_), weapons(weapons_){}

BattleShip::BattleShip(ShipType type, const std::string &name_, const Capitan &capitan_, double speed_,
     double max_speed_, int hp_, int max_hp_, int price_) : Ship(type, name_, capitan_, speed_,
     max_speed_, hp_, max_hp_, price_) {}

// модифицировать вооружение --------------------------
void BattleShip::modify_weapon(int number, WeaponName weapon) {
    Battle::modify_weapon<BattleShip>(*this, number, weapon);
}

// информация об оружии в данном участке корабля -----------------
Weapon BattleShip::info_weapon(int number) const {
    return Battle::info_weapon<BattleShip>(*this, number);
}

// выстрел из всех орудий ------------------------------
int BattleShip::shoot(int x, int y) noexcept{
    return Battle::shoot<BattleShip>(*this, x, y);
}

// ------------------ Военный транспорт ------------------

BattleTransport::BattleTransport() noexcept : TransportShip() {
    set_name(BATTLETRANSPORT);
}

BattleTransport::BattleTransport(const std::string &name_, const Capitan &capitan_, double speed_,
        double max_speed_, int hp_, int max_hp_, int price_, int weight_, int max_weight_,
        const std::array<Weapon, 4> &weapons_)
        : TransportShip(name_, capitan_, speed_, max_speed_, hp_, max_hp_, price_, weight_, max_weight_), weapons(weapons_){
    set_name(BATTLETRANSPORT);
}

BattleTransport::BattleTransport(const std::string &name_, const Capitan &capitan_, double speed_, double max_speed_,
       int hp_, int max_hp_, int price_, int weight_, int max_weight_) :
       TransportShip(name_, capitan_, speed_, max_speed_, hp_, max_hp_, price_, weight_, max_weight_){
    set_name(BATTLETRANSPORT);
}


void BattleTransport::modify_weapon(int number, WeaponName weapon) {
    Battle::modify_weapon<BattleTransport>(*this, number, weapon);
}

Weapon BattleTransport::info_weapon(int number) const {
    return Battle::info_weapon<BattleTransport>(*this, number);
}

int BattleTransport::shoot(int x, int y) noexcept{
    return Battle::shoot<BattleTransport>(*this, x, y);
}


// ------------ общие функции для военных кораблей ---------------------

namespace Battle{
    template <class T>
    void modify_weapon(T& ship, int number, WeaponName weapon){
        if (number > 4 || number <= 0){
            throw std::invalid_argument("Can`t set new weapon here");
        }
        std::vector<Weapon> data = set_weapon(); // загружаем массив доступного вооружения
        Weapon new_weapon;
        for (Weapon const &i : data){
            if (weapon == i.get_name()){
                new_weapon = i;
                break;
            }
        }
        if (new_weapon.get_name() == UNDEFINED){
            throw std::invalid_argument("Can`t find this weapon in data!");
        }
        ship.set_weapons(new_weapon, number);
    }

    template <class T>
    Weapon info_weapon(T const &ship, int number){
        if (number > 4 || number <= 0){
            throw std::invalid_argument("Can`t set new weapon here");
        }
        return ship.get_weapons(number);
    }

    template <class T>
    int shoot(T &ship, int x, int y) noexcept{
        int sum_damage = 0;
        double range = sqrt(pow(x, 2) + pow(y, 2));
        std::array<Weapon, 4> wp = ship.get_wp();
        for (Weapon &i : wp){
            if (i.get_range() >= range){
                sum_damage += i.shoot();
            }
        }
        return sum_damage;
    }
}

//---------------------------------------------------

std::vector<Weapon> set_weapon(){
    std::vector<Weapon> store;
    Weapon wp1(BIG, 100, 1, 100, 10, 10, 10000);
    Weapon wp2(MEDIUM, 50, 2, 50, 30, 30, 4000);
    Weapon wp3(SMALL, 10, 15, 10, 200, 200, 2000);
    store.push_back(wp1);
    store.push_back(wp2);
    store.push_back(wp3);
    return store;
}

std::vector<std::shared_ptr<Ship>> set_ships(){
    std::vector<std::shared_ptr<Ship>> store;
    Capitan cap;
    store.push_back(std::make_shared<TransportShip>("convoy", cap, 30, 30, 1000, 1000, 3000, 0, 200));
    store.push_back(std::make_shared<BattleTransport>("battle convoy", cap, 25, 25, 1000, 1000, 5000, 0, 50));
    store.push_back(std::make_shared<BattleShip>(DESTROYER, "destroyer", cap, 30, 30, 1500, 1500, 4000));
    store.push_back(std::make_shared<BattleShip>(LCRUISER, "light cruiser", cap, 25, 25, 2500, 2500, 6000));
    store.push_back(std::make_shared<BattleShip>(HCRUISER, "heavy cruiser", cap, 18, 18, 4000, 4000, 9000));
    store.push_back(std::make_shared<BattleShip>(BATTLESHIP, "battle ship", cap, 12, 12, 9000, 9000, 14000));
    return store;
}