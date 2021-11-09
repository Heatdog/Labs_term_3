//
// Created by User on 07.11.2021.
//

#include "Mission.h"

// --------- Конструкторы/деструкторы/сеттеры/геттеры ---------------

Mission::Mission(){
    table_pirate = new Table;
    table_convoy = new Table;
    max_convoy = 10;
    max_pirate = 10;
    set_pirates();
    if (table_pirate->count() > max_pirate){
        throw std::invalid_argument("Too many pirate ships");
    }
    money = 100000;
    spent_money = 0;
    weight = 0;
    max_weight = 200;
}

Mission::~Mission(){
    delete table_pirate;
    delete table_convoy;
}

// если генерируется invalid_argument - продолжаем вставку, но с выкидыванием исключения выше для обработки
void Mission::set_pirates() {
    try {
        try{
            insert_pirate(DESTROYER, "pirate1", SMALL, SMALL, SMALL, SMALL);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(LCRUISER, "pirate2", SMALL, MEDIUM, MEDIUM, BIG);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(HCRUISER, "pirate3", MEDIUM, MEDIUM, MEDIUM, BIG);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(BATTLESHIP, "pirate4", BIG, BIG, BIG, BIG);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(DESTROYER, "pirate5", SMALL, SMALL, SMALL, SMALL);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
    } catch (std::range_error const &err) {
        throw err;
    }
}

// ---------- Публичные методы -------------

// ------------- Пираты --------------------

// получить ссылку на корабль пиратов
std::shared_ptr<Ship> Mission::get_pirate(std::string const &name) const {
    try{
        return get_pirate_table()->find(name);
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// внести в таблицу новый корабль пиратов
void Mission::insert_pirate(ShipType type, std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4) const {
    if (get_pirate_table()->count() + 1 > max_pirate){
        throw std::range_error("Too many pirates!");
    }
    try{
        std::shared_ptr<Ship> sp = std::make_shared<BattleShip>(type, name, wp1, wp2, wp3, wp4);
        get_pirate_table()->insert(sp);
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// уничтожить корабль пиратов
void Mission::erase_pirate(const std::string &name) const {
    try{
        get_pirate_table()->erase(name);
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// ---------------------------------------

// ------------------ Конвой ------------------

// покупка военного корабля
void Mission::buy_convoy_battle(ShipType type, const std::string &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4){
    if (get_convoy_table()->count() + 1 > max_convoy){
        throw std::range_error("Too many convoys!");
    }
    try{
        get_convoy_table()->insert(std::make_shared<BattleShip>(type, name, wp1, wp2, wp3, wp4));
        if (spent_money + get_convoy(name)->get_price() > money){ // вставка удалась, но корабль слишком дорогой
            erase_convoy(name);
            throw std::overflow_error("Too many money!");
        }
        spent_money += get_convoy(name)->get_price();
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// покупка транспортного конвоя
void Mission::buy_convoy_transport(const std::string &name, int weight_) {
    if (get_convoy_table()->count() + 1 > max_convoy){
        throw std::range_error("Too many convoys!");
    }
    try{
        get_convoy_table()->insert(std::make_shared<TransportShip>(name, weight_));
        if (spent_money + get_convoy(name)->get_price() > money){ // вставка удалась, но корабль слишком дорогой
            erase_convoy(name);
            throw std::overflow_error("Too many money!");
        }
        spent_money += get_convoy(name)->get_price();
        weight += weight_; // увеличиваем общую массу груза
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// покупка военного транспорта
void Mission::buy_convoy_battle_transport(const std::string &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4, int weight_)  {
    if (get_convoy_table()->count() + 1 > max_convoy){
        throw std::range_error("Too many convoys!");
    }
    try{
        get_convoy_table()->insert(std::make_shared<BattleTransport>(name, wp1, wp2, wp3, wp4, weight_));
        if (spent_money + get_convoy(name)->get_price() > money) { // вставка удалась, но корабль слишком дорогой
            erase_convoy(name);
            throw std::overflow_error("Too many money!");
        }
        spent_money += get_convoy(name)->get_price();
        weight += weight_; // увеличиваем общую массу груза

    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// получить указатель на корабль конвоя
std::shared_ptr<Ship> Mission::get_convoy(const std::string &name) const {
    try {
        return get_convoy_table()->find(name);
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// уничтожить корабль конвоя
void Mission::erase_convoy(const std::string &name) const {
    try{
        get_convoy_table()->erase(name);
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// кол-во кораблей
unsigned long Mission::count_pirates() const noexcept {
    return get_pirate_table()->count();
}

unsigned long Mission::count_convoy() const noexcept {
    return get_convoy_table()->count();
}

// покупка вооружения
void Mission::buy_weapon(const std::string &name_, WeaponName type_, int number) {
    try{
        std::shared_ptr<Ship> sh = get_convoy(name_);
        Weapon wp = sh->get_weapons(number); // старое вооружение
        int x = sh->get_price(); // получаем цену до модификации
        sh->modify_weapon(number, type_); // модифицируем
        if (spent_money + (sh->get_price() - x) > money){ // если цена слишком большая - устанавливаем старое
            sh->modify_weapon(number, wp.get_name());
            throw std::overflow_error("Too many money!");
        }
        spent_money += sh->get_price() - x; // увеличиваем на разность стоимости кораблей с вооружением и без
    }catch (std::invalid_argument const &err){
        throw err;
    }catch (std::out_of_range const &err){
        throw err;
    }
}

// продажа вооружения
void Mission::sell_weapon(const std::string &name_, int number) {
    try{
        std::shared_ptr<Ship> sh = get_convoy(name_);
        int x = sh->get_price(); // получаем цену до модификации
        sh->modify_weapon(number, UNDEFINED);
        spent_money += sh->get_price() - x; // уменьшаем цену благодаря разности
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// продажа корабля конвоя
void Mission::sell_convoy(const std::string &name_) {
    try{
        std::shared_ptr<Ship> sp = get_convoy(name_);
        int price_ = static_cast<int>(sp->get_price());
        erase_convoy(name_);
        spent_money -= price_; // уменьшаем стоимость на цену корабля
    }catch (std::invalid_argument const &err){
        throw err;
    }
}
