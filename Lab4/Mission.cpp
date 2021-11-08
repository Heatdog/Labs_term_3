//
// Created by User on 07.11.2021.
//

#include "Mission.h"

// --------- Конструкторы/деструкторы/сеттеры/геттеры ---------------

Mission::Mission(){
    table_pirate = new Table;
    table_convoy = new Table;
    set_pirates();
    if (table_pirate->count() > max_pirate){
        throw std::invalid_argument("Too many pirate ships");
    }
    money = 100000;
    spent_money = 0;
    weight = 0;
}

Mission::~Mission(){
    delete table_pirate;
    delete table_convoy;
}

void Mission::set_pirates() {
    bool shp1 = table_pirate->insert(std::make_shared<BattleShip>(DESTROYER, "pirate1", SMALL, SMALL, SMALL, SMALL));
    bool shp2 = table_pirate->insert(std::make_shared<BattleShip>(LCRUISER, "pirate2", SMALL, MEDIUM, MEDIUM, BIG));
    bool shp3 = table_pirate->insert(std::make_shared<BattleShip>(HCRUISER, "pirate3", MEDIUM, MEDIUM, MEDIUM, BIG));
    bool shp4 = table_pirate->insert(std::make_shared<BattleShip>(BATTLESHIP, "pirate4", BIG, BIG, BIG, BIG));
    bool shp5 = table_pirate->insert(std::make_shared<BattleShip>(DESTROYER, "pirate5", SMALL, SMALL, SMALL, SMALL));
    if (!(shp1 && shp2 && shp3 && shp4 && shp5)){
        throw std::runtime_error("Duplicates!");
    }
}

// ---------- Публичные методы -------------

// ------------- Пираты --------------------

// получить ссылку на корабль пиратов
std::shared_ptr<Ship> Mission::get_pirate(std::string const &name) const noexcept {
    return get_pirate_table()->find(name);
}

// внести в таблицу новый корабль пиратов
bool Mission::insert_pirate(ShipType type, std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4) const noexcept {
    if (get_pirate_table()->count() + 1 > max_pirate){
        return false;
    }
    std::shared_ptr<Ship> sp = std::make_shared<BattleShip>(type, name, wp1, wp2, wp3, wp4);
    return get_pirate_table()->insert(sp);
}

// удалить корабль пиратов
bool Mission::erase_pirate(const std::string &name) const {
    return get_pirate_table()->erase(name) == 1;
}

// ---------------------------------------

// ------------------ Конвой ------------------

// добавление военного корабля
bool Mission::insert_convoy_battle(ShipType type, const std::string &name, WeaponName wp1, WeaponName wp2,
                                   WeaponName wp3, WeaponName wp4){
    if (get_convoy_table()->count() + 1 > max_convoy){
        return false;
    }
    if(get_convoy_table()->insert(std::make_shared<BattleShip>(type, name, wp1, wp2, wp3, wp4))){
        if (spent_money + get_convoy(name)->get_price() > money){ // вставка удалась, но корабль слишком дорогой
            erase_convoy(name);
            return false;
        } else{
            spent_money += get_convoy(name)->get_price();
            return true;
        }
    } else{
        return false;
    }
}

// Добавление транспортного конвоя
bool Mission::insert_convoy_transport(const std::string &name, int weight_) {
    if (get_convoy_table()->count() + 1 > max_convoy){
        return false;
    }
    if (get_convoy_table()->insert(std::make_shared<TransportShip>(name, weight_))){
        if (spent_money + get_convoy(name)->get_price() > money){ // вставка удалась, но корабль слишком дорогой
            erase_convoy(name);
            return false;
        } else{
            spent_money += get_convoy(name)->get_price();
            weight += weight_; // увеличиваем общую массу груза
            return true;
        }
    } else{
        return false;
    }
}

// Добавление военного транспорта
bool Mission::insert_convoy_battle_transport(const std::string &name, WeaponName wp1, WeaponName wp2, WeaponName wp3,
                                             WeaponName wp4, int weight_)  {
    if (get_convoy_table()->count() + 1 > max_convoy){
        return false;
    }
    if (get_convoy_table()->insert(std::make_shared<BattleTransport>(name, wp1, wp2, wp3, wp4, weight_))){
        if (spent_money + get_convoy(name)->get_price() > money) { // вставка удалась, но корабль слишком дорогой
            erase_convoy(name);
            return false;
        } else{
            spent_money += get_convoy(name)->get_price();
            weight += weight_; // увеличиваем общую массу груза
            return true;
        }
    } else{
        return false;
    }
}

// получить указатель на корабль конвоя
std::shared_ptr<Ship> Mission::get_convoy(const std::string &name) const noexcept {
    return get_convoy_table()->find(name);
}

// удалить корабль конвоя
bool Mission::erase_convoy(const std::string &name) const {
    return get_convoy_table()->erase(name) == 1;
}

// кол-во кораблей
unsigned long Mission::count_pirates() const noexcept {
    return get_pirate_table()->count();
}

unsigned long Mission::count_convoy() const noexcept {
    return get_convoy_table()->count();
}

// покупка вооружения
bool Mission::buy_weapon(const std::string &name_, WeaponName type_, int number) {
    std::shared_ptr<Ship> sh = get_convoy_table()->find(name_);
    if (sh == nullptr){
        return false;
    }
    Weapon wp = sh->get_weapons(number); // старое вооружение
    int x = sh->get_price(); // получаем цену до модификации
    sh->modify_weapon(number, type_); // модифицируем
    if (spent_money + (sh->get_price() - x) > money){ // если цена слишком большая - устанавливаем старое
        sh->modify_weapon(number, wp.get_name());
        return false;
    } else{
        spent_money += sh->get_price() - x; // увеличиваем на разность стоимости кораблей с вооружением и без
        return true;
    }
}

// продажа вооружения
bool Mission::sell_weapon(const std::string &name_, int number) {
    std::shared_ptr<Ship> sh = get_convoy_table()->find(name_);
    int x = sh->get_price(); // получаем цену до модификации
    if (sh == nullptr){
        return false;
    }
    sh->modify_weapon(number, UNDEFINED);
    spent_money += sh->get_price() - x; // уменьшаем цену благодаря разности
    return true;
}