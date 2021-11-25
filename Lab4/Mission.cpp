//
// Created by User on 07.11.2021.
//

#include "Mission.h"

// --------- Конструкторы/деструкторы/сеттеры/геттеры ---------------

Mission::Mission() : money(100000), max_weight(200){
    table_pirate = new Table;
    table_convoy = new Table;
    max_convoy = 10;
    max_pirate = 10;
    set_pirates();
    if (table_pirate->count() > max_pirate){
        throw std::invalid_argument("Too many pirate ships");
    }
    spent_money = 0;
    weight = 0;
    weight_lost = 0;
    weight_delivered = 0;
}

Mission::~Mission(){
    delete table_pirate;
    delete table_convoy;
}

// если генерируется invalid_argument - продолжаем вставку, но с выкидыванием исключения выше для обработки
void Mission::set_pirates() const { // можно для пиратов сделать id
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
std::shared_ptr<Ship> Mission::get_pirate(unsigned long const &id) const {
    try{
        return get_pirate_table()->find(id);
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// внести в таблицу новый корабль пиратов
unsigned long Mission::insert_pirate(ShipType type, std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4) const {
    if (get_pirate_table()->count() + 1 > max_pirate){
        throw std::range_error("Too many pirates!");
    }
    try{
        std::shared_ptr<Ship> sp = std::make_shared<BattleShip>(type, name, wp1, wp2, wp3, wp4);
        return get_pirate_table()->insert(sp);
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// уничтожить корабль пиратов
void Mission::erase_pirate(unsigned long const &id) const {
    try{
        get_pirate_table()->erase(id);
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// ---------------------------------------

// ------------------ Конвой ------------------

// покупка военного корабля
unsigned long Mission::buy_convoy_battle(ShipType type, const std::string &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4){
    if (get_convoy_table()->count() + 1 > max_convoy){
        throw std::range_error("Too many convoys!");
    }
    try{
        unsigned long id = get_convoy_table()->insert(std::make_shared<BattleShip>(type, name, wp1, wp2, wp3, wp4));
        if (spent_money + get_convoy(id)->get_price() > money){ // вставка удалась, но корабль слишком дорогой
            erase_convoy(id);
            throw std::overflow_error("Too many money!");
        }
        spent_money += get_convoy(id)->get_price();
        return id;
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// покупка транспортного конвоя
unsigned long Mission::buy_convoy_transport(const std::string &name, int weight_) {
    if (get_convoy_table()->count() + 1 > max_convoy){
        throw std::range_error("Too many convoys!");
    }
    if (weight_ + weight > max_weight){
        throw std::invalid_argument("Too big weight");
    }
    try{
        unsigned long id = get_convoy_table()->insert(std::make_shared<TransportShip>(name, weight_));
        if (spent_money + get_convoy(id)->get_price() > money){ // вставка удалась, но корабль слишком дорогой
            erase_convoy(id);
            throw std::overflow_error("Too many money!");
        }
        spent_money += get_convoy(id)->get_price();
        weight += weight_; // увеличиваем общую массу груза
        return id;
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// покупка военного транспорта
unsigned long Mission::buy_convoy_battle_transport(const std::string &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4, int weight_)  {
    if (get_convoy_table()->count() + 1 > max_convoy){
        throw std::range_error("Too many convoys!");
    }
    if (weight_ + weight > max_weight){
        throw std::invalid_argument("Too big weight");
    }
    try{
        unsigned long id = get_convoy_table()->insert(std::make_shared<BattleTransport>(name, wp1, wp2, wp3, wp4, weight_));
        if (spent_money + get_convoy(id)->get_price() > money) { // вставка удалась, но корабль слишком дорогой
            erase_convoy(id);
            throw std::overflow_error("Too many money!");
        }
        spent_money += get_convoy(id)->get_price();
        weight += weight_; // увеличиваем общую массу груза
        return id;
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// получить указатель на корабль конвоя
std::shared_ptr<Ship> Mission::get_convoy(unsigned long const &id) const {
    try {
        return get_convoy_table()->find(id);
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// уничтожить корабль конвоя
void Mission::erase_convoy(unsigned long const &id) {
    try{
        int weight_ = get_convoy(id)->get_weight();
        get_convoy_table()->erase(id);
        weight_lost += weight_;
        weight -= weight_;
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
void Mission::buy_weapon(unsigned long const &id, WeaponName type_, int number) {
    try{
        std::shared_ptr<Ship> sh = get_convoy(id);
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
void Mission::sell_weapon(unsigned long const &id, int number) {
    try{
        std::shared_ptr<Ship> sh = get_convoy(id);
        int x = sh->get_price(); // получаем цену до модификации
        sh->modify_weapon(number, UNDEFINED);
        spent_money += sh->get_price() - x; // уменьшаем цену благодаря разности
    }catch (std::invalid_argument const &err){
        throw err;
    }catch (std::out_of_range const &err){
        throw err;
    }
}

// продажа корабля конвоя
void Mission::sell_convoy(unsigned long const &id) {
    try{
        std::shared_ptr<Ship> sp = get_convoy(id);
        int price_ = static_cast<int>(sp->get_price());
        int weight_ = sp->get_weight();
        erase_convoy(id);
        spent_money -= price_; // уменьшаем стоимость на цену корабля
        weight_lost -= weight_;
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// загрузка груза на корабль
void Mission::upload_weight(unsigned long const &id, int weight_) {
    if (weight_ + weight > max_weight || weight_ < 0){ // отрицательное значение или потенциально слишком большое
        throw std::invalid_argument("Invalid weight!");
    }
    try {
        std::shared_ptr<Ship> sh = get_convoy(id);
        if (sh->get_max_weight() == 0){
            throw std::invalid_argument("Invalid ship!");
        }
        sh->add_weight(weight_);
        weight += weight_;
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// разгрузка корабля
void Mission::unload_weight(unsigned long const &id, int weight_) {
    if (weight_ < 0 || weight_ > weight){
        throw std::invalid_argument("Invalid weight!");
    }
    try{
        std::shared_ptr<Ship> sh = get_convoy(id);
        if (sh->get_max_weight() == 0){
            throw std::invalid_argument("Invalid ship!");
        }
        if (sh->get_weight() < weight_){
            throw std::invalid_argument("Invalid weight!");
        }
        sh->add_weight(-weight_);
        weight -= weight_;
    }catch (std::invalid_argument const &err){
        throw err;
    }
}

// кол-во транспортных кораблей/военного транспорта/военных кораблей
int Mission::number_convoy_transport() noexcept {
    return table_convoy->count_transport();
}

int Mission::number_convoy_battle_transport() noexcept {
    return table_convoy->count_battle_transport();
}


// автоматическая загрузка всего груза
void Mission::upload_automatically() { // подгрузка кораблей
    std::shared_ptr<Ship> transport = get_ship_type_info(TRANSPORT);
    std::shared_ptr<Ship> battle_transport = get_ship_type_info(BATTLETRANSPORT);
    try {
        if ((number_convoy_transport() * transport->get_max_weight()) + (number_convoy_battle_transport() * battle_transport->get_max_weight()) < get_max_weight()){
            throw std::invalid_argument("too low ships");
        }
        int f = transport->get_max_weight()/battle_transport->get_max_weight() + 1;
        int g = 1;
        if (number_convoy_transport() != 0){
            g = number_convoy_transport();
        }
        int k = (get_max_weight() / (f * (number_convoy_transport() + number_convoy_battle_transport()))) * (number_convoy_battle_transport()/g); // 1/5 часть среднего распределения (общее распределение на 4 конвоя 1 военный транспорт)
        int weight_max_ = 0;
        if (g != 0){
            weight_max_ = (get_max_weight() - k * number_convoy_battle_transport())/g;
        }
        auto table = table_convoy->get_table();
        weight = 0;
        for (auto const &i: table) {
            if (i.second.ship->get_type() == TRANSPORT || i.second.ship->get_type() == BATTLETRANSPORT) {
                int x;
                i.second.ship->get_type() == TRANSPORT ?  x = weight_max_ - i.second.ship->get_weight() : x = k - i.second.ship->get_weight();
                weight +=  i.second.ship->get_weight(); // Увеличиваю на старое значение, т.к. потом увеличивается только на добавление веса
                if (x > 0){
                    upload_weight(i.first, x);
                } else if (x < 0){
                    unload_weight(i.first, -x);
                }
            }
        }
    }catch (std::invalid_argument const &err){
        throw err;
    }
}
