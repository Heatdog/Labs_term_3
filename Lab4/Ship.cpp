//
// Created by User on 31.10.2021.
//

#include "Ship.h"

#include <utility>

// ----------- Капитан ----------------------

Capitan &Capitan::operator=(const Capitan &a) {
    if (this != &a){
        name.clear();
        name = a.name;
        rang = a.rang;
    }
    return *this;
}

// ----------- Вооружение --------------------

Weapon::Weapon() noexcept : name(UNDEFINED), damage(0), rate(0), range(0), max_ammo(0), ammo(0), price(0) {}

Weapon::Weapon(WeaponName name_, int damage_, int rate_, double range_, int max_ammo_, int ammo_, int price_)
    :name(name_), damage(damage_), rate(rate_), range(range_), max_ammo(max_ammo_), ammo(ammo_), price(price_){
    if (damage < 0 || rate < 0 || range < 0 || max_ammo < 0 || ammo < 0 || price < 0){
        throw std::invalid_argument("Inv arg! Weapon constructor");
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
    if (rate > ammo){
        ammo -= rate;
        return damage*rate;
    } else{
        int damage_ = damage*ammo;
        ammo = 0;
        return damage_;
    }
}

int Weapon::shoot_test() const noexcept {
    if (rate > ammo){
        return damage*rate;
    } else{
        int damage_ = damage*ammo;
        return damage_;
    }
}

void Weapon::print_type() const noexcept {
    if (name == SMALL){
        std::cout << "Малокалиберное";
    } else if (name == MEDIUM){
        std::cout << "Среднекалиберное";
    } else if (name == BIG){
        std::cout << "Крупнокалиберное";
    } else if (name == UNDEFINED){
        std::cout << "Не установлено";
    }
}

// ---------------- Корабль (базовый класс для всего остального) -------------------------

Ship::Ship() noexcept : type(UNDEFINEDSHIP), capitan(Capitan()), speed(0), max_speed(0), hp(0),
    max_hp(0), price(0){
}


Ship::Ship(ShipType type_, std::string name_, Capitan const &capitan_, double speed_, double max_speed_, int hp_, int max_hp_,
    int price_) : type(type_), name(std::move(name_)), capitan(capitan_), speed(speed_), max_speed(max_speed_),
    hp(hp_), max_hp(max_hp_), price(price_){
    if (speed < 0 || max_speed < 0 || hp < 0 || max_hp < 0 || (max_speed < speed)){
        throw std::invalid_argument("Invalid arg! Ship constructor (base class)");
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
        file = a.file;
        image = a.image;
        texture = a.texture;
        sprite = a.sprite;
    }
    return *this;
}

// получить попадание -------------------
void Ship::take_damage(int damage)  {
    if (damage < 0){
        throw std::invalid_argument("Inv arg! damage");
    }
    hp -= damage;
}

void Ship::set_speed(double speed_){
    if (speed_ < 0 || speed_ > max_speed){
        throw std::invalid_argument("Inv arg! speed");
    }
    speed = speed_;
}

void Ship::set_max_speed(double max_speed_) {
    if (max_speed_ < 0 || max_speed_ < speed){
        throw std::invalid_argument("Inv arg! max speed");
    }
    max_speed = max_speed_;
}

void Ship::set_hp(int hp_) {
    if (hp_ < 0){
        throw std::invalid_argument("Inv arg! hp");
    }
    hp = hp_;
}

void Ship::set_max_hp(int hp_){
    if (hp_ < 0){
        throw std::invalid_argument("Inv arg! max hp");
    }
    max_hp = hp_;
}

void Ship::set_price(int price_){
    if (price_ < 0){
        throw std::invalid_argument("Inv arg! price");
    }
    price = price_;
}

void Ship::increase_price(int price_) noexcept{
    price += price_;
}

void Ship::print_type() const noexcept {
    if (type == TRANSPORT){
        std::cout << "Транспортный";
    } else if (type == BATTLETRANSPORT){
        std::cout << "Военный транспорт";
    } else if (type == DESTROYER){
        std::cout << "Эсминец";
    } else if (type == LCRUISER){
        std::cout << "Легкий крейсер";
    } else if (type == HCRUISER){
        std::cout << "Тяжелый крейсер";
    } else if (type == BATTLESHIP){
        std::cout << "Линкор";
    }
}

// ---------------------- Транспортный корабль -----------------------

TransportShip::TransportShip() noexcept : Ship(), weight(0), max_weight(0), ratio(1) {
    set_type(TRANSPORT);
    set_name("transport");
    file = "TransportImage.png";
    image.loadFromFile("../Images/TransportImage.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

TransportShip::TransportShip(std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
    int hp_, int max_hp_, int price_, int weight_, int max_weight_)
    try : Ship(TRANSPORT, name_, capitan_, speed_, max_speed_, hp_, max_hp_, price_),
    max_weight(max_weight_), ratio(1) {
    if (weight_ < 0 || max_weight_ < 0){
        throw std::invalid_argument("Invalid arg! TransportShip constructor");
    }
    set_weight(weight_);
    file = "TransportImage.png";
    image.loadFromFile("../Images/TransportImage.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}catch (std::invalid_argument const &err){
    throw err;
}

TransportShip::TransportShip(const std::string &name_, int weight_) {
    if (weight_ < 0){
        throw std::invalid_argument("Invalid arg! TransportShip constructor");
    }
    auto data_sh = set_ships();
    for (const std::shared_ptr<Ship>&  i : data_sh){
        if (i->get_type() == TRANSPORT){
            set_name(name_);
            set_type(TRANSPORT);
            set_cap(i->get_cap());
            set_max_speed(i->get_max_speed());
            set_speed(i->get_speed());
            set_hp(i->get_hp());
            set_max_hp(i->get_max_hp());
            set_price(i->get_price());
            set_max_weight(i->get_max_weight());
            set_weight(weight_);
            file = "TransportImage.png";
            image.loadFromFile("../Images/TransportImage.png");
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            break;
        }
    }
}

// установить вес ------------------------
void TransportShip::add_weight(int amount) {
    try {
        double rat = 1;
        if (amount + weight > 0){
            rat = 1-static_cast<double >(amount + weight)/static_cast<double >(max_weight);
        }
        set_ratio(rat);
        double new_speed = get_max_speed()*rat;
        set_speed(new_speed);
        if (amount + weight > 0){
            weight += amount;
        } else{
            weight = 0;
        }
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// установить вес
void TransportShip::set_weight(int amount) {
    weight = 0;
    add_weight(amount);
}

// установить макс вес
void TransportShip::set_max_weight(int weight_){
    if (weight_ < 0){
        throw std::invalid_argument("Inv arg! set max weight");
    }
    max_weight = weight_;
}

// определить макс скорость при выбранной нагрузке -----------------
double TransportShip::new_max_speed(int weight_) {
    if (weight_ < 0){
        throw std::invalid_argument("Inv arg! new max speed");
    }
    return get_max_speed()*(1-static_cast<double >(weight_)/static_cast<double >(max_weight));
}

void TransportShip::set_ratio(double rat_) {
    if (rat_ < 0 || rat_ > 1){
        throw std::invalid_argument("Inv arg! set ratio");
    }
    ratio = rat_;
}

// --------------------- Военный корабль -------------------

BattleShip::BattleShip() noexcept : Ship() {
    set_type(BATTLESHIP);
    set_name("battleship");
    file = "BattleImage.png";
    image.loadFromFile("../Images/BattleImage.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

BattleShip::BattleShip(ShipType type, const std::string &name_, const Capitan &capitan_, double speed_, double max_speed_,
     int hp_, int max_hp_, int price_, std::array<Weapon, 4> weapons_)
     : Ship(type, name_, capitan_, speed_, max_speed_, hp_, max_hp_, price_), weapons(std::move(weapons_)){
        if (type == DESTROYER){
            file = "DestroyerImage.png";
        }else if (type == LCRUISER){
            file = "LightCrImage.png";
        } else if (type == HCRUISER){
            file = "HeavyCrImage.png";
        } else if (type == BATTLESHIP){
            file = "BattleImage.png";
        } else if (type == BATTLETRANSPORT){
            file = "BattleTransportImage.png";
        }
        image.loadFromFile("../Images/" + file);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }

BattleShip::BattleShip(ShipType type, const std::string &name_, const Capitan &capitan_, double speed_,
     double max_speed_, int hp_, int max_hp_, int price_) : Ship(type, name_, capitan_, speed_,
     max_speed_, hp_, max_hp_, price_) {
    if (type == DESTROYER){
        file = "DestroyerImage.png";
    }else if (type == LCRUISER){
        file = "LightCrImage.png";
    } else if (type == HCRUISER){
        file = "HeavyCrImage.png";
    } else if (type == BATTLESHIP){
        file = "BattleImage.png";
    } else if (type == BATTLETRANSPORT){
        file = "BattleTransportImage.png";
    }
    image.loadFromFile("../Images/" + file);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    }

BattleShip::BattleShip(ShipType type_, const std::string &name_, WeaponName wp1, WeaponName wp2, WeaponName wp3,
    WeaponName wp4) {
    auto data_sh = set_ships();
    for (const std::shared_ptr<Ship>&  i : data_sh){
        if (i->get_type() == type_){
            set_name(name_);
            set_type(type_);
            set_cap(i->get_cap());
            set_max_speed(i->get_max_speed());
            set_speed(i->get_speed());
            set_hp(i->get_hp());
            set_max_hp(i->get_max_hp());
            set_price(i->get_price());
            modify_weapon(1, wp1);
            modify_weapon(2, wp2);
            modify_weapon(3, wp3);
            modify_weapon(4, wp4);
            if (get_type() == DESTROYER){
                file = "DestroyerImage.png";
            }else if (get_type() == LCRUISER){
                file = "LightCrImage.png";
            } else if (get_type() == HCRUISER){
                file = "HeavyCrImage.png";
            } else if (get_type() == BATTLESHIP){
                file = "BattleImage.png";
            } else if (get_type() == BATTLETRANSPORT){
                file = "BattleTransportImage.png";
            }
            image.loadFromFile("../Images/" + file);
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            break;
        }
    }
}

// модифицировать вооружение --------------------------
void BattleShip::modify_weapon(int number, WeaponName weapon) {
    Battle::modify_weapon<BattleShip>(*this, number, weapon);
}

// информация об оружии в данном участке корабля -----------------
Weapon BattleShip::info_weapon(int number) const {
    return Battle::info_weapon<BattleShip>(*this, number);
}
// ------------------ Военный транспорт ------------------

BattleTransport::BattleTransport() noexcept : TransportShip() {
    set_type(BATTLETRANSPORT);
    set_name("battle convoy");
}

BattleTransport::BattleTransport(const std::string &name_, const Capitan &capitan_, double speed_,
        double max_speed_, int hp_, int max_hp_, int price_, int weight_, int max_weight_,
        std::array<Weapon, 4> weapons_)
        : TransportShip(name_, capitan_, speed_, max_speed_, hp_, max_hp_, price_, weight_, max_weight_), weapons(std::move(weapons_)){
    set_type(BATTLETRANSPORT);
}

BattleTransport::BattleTransport(const std::string &name_, const Capitan &capitan_, double speed_, double max_speed_,
       int hp_, int max_hp_, int price_, int weight_, int max_weight_) :
       TransportShip(name_, capitan_, speed_, max_speed_, hp_, max_hp_, price_, weight_, max_weight_){
    set_type(BATTLETRANSPORT);
}

BattleTransport::BattleTransport(const std::string &name_, WeaponName wp1, WeaponName wp2, WeaponName wp3,
                                 WeaponName wp4, int weight_) {
    if (weight_ < 0){
        throw std::invalid_argument("Invalid arg! weight");
    }
    auto data_sh = set_ships();
    for (const std::shared_ptr<Ship>&  i : data_sh){
        if (i->get_type() == BATTLETRANSPORT){
            set_weight(0);
            set_name(name_);
            set_type(BATTLETRANSPORT);
            set_cap(i->get_cap());
            set_max_speed(i->get_max_speed());
            set_speed(i->get_speed());
            set_hp(i->get_hp());
            set_max_hp(i->get_max_hp());
            set_price(i->get_price());
            modify_weapon(1, wp1);
            modify_weapon(2, wp2);
            modify_weapon(3, wp3);
            modify_weapon(4, wp4);
            set_max_weight(i->get_max_weight());
            set_weight(weight_);
            break;
        }
    }

}

void BattleTransport::modify_weapon(int number, WeaponName weapon) {
    Battle::modify_weapon<BattleTransport>(*this, number, weapon);
}

Weapon BattleTransport::info_weapon(int number) const {
    return Battle::info_weapon<BattleTransport>(*this, number);
}

// ------------ общие функции для военных кораблей ---------------------

namespace Battle{
    template <class T>
    void modify_weapon(T& ship, int number, WeaponName weapon){
        if (number > 4 || number <= 0){
            throw std::out_of_range("Inv arg! number");
        }
        std::vector<Weapon> data = set_weapon(); // загружаем массив доступного вооружения
        Weapon new_weapon;
        for (Weapon const &i : data){
            if (weapon == i.get_name()){
                new_weapon = i;
                ship.increase_price(i.get_price() - ship.get_weapons(number).get_price()); // изменяем цен
                break;
            }
        }
        ship.set_weapons(new_weapon, number);
    }

    template <class T>
    Weapon info_weapon(T const &ship, int number){
        if (number > 4 || number <= 0){
            throw std::out_of_range("Can`t set new weapon here");
        }
        return ship.get_weapons(number);
    }
}

//---------------------------------------------------

std::vector<Weapon> set_weapon(){
    std::vector<Weapon> store;
    Weapon wp1(BIG, 100, 1, 100, 10, 10, 10000);
    Weapon wp2(MEDIUM, 50, 2, 50, 30, 30, 4000);
    Weapon wp3(SMALL, 10, 15, 10, 200, 200, 2000);
    Weapon wp4(UNDEFINED, 0, 0, 0, 0, 0, 0);
    store.push_back(wp1);
    store.push_back(wp2);
    store.push_back(wp3);
    store.push_back(wp4);
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

std::shared_ptr<Ship> get_ship_type_info(ShipType type_) {
    std::vector<std::shared_ptr<Ship>> data_ = set_ships();
    for (auto const &i : data_){
        if (i->get_type() == type_){
            return i;
        }
    }
    return nullptr;
}