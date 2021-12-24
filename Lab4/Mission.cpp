//
// Created by User on 07.11.2021.
//

#include "Mission.h"

Map::Map(int p_x, int p_y, Table* table_convoy_, Table* table_pirate_) noexcept : table_convoy(table_convoy_), table_pirate(table_pirate_){
    for (int i = 0; i < distance; i++){
        map[0][i] = "-";
        map[height-1][i] = "-";
    }
    for (int k = 0; k < distance; k++){
        for (int j = 1; j < height-1; j++){
            map[j][k] = " ";
        }
    }
    map[height/2][0] = "<";
    map[height/2][distance-1] = ">";
    map[p_y][p_x] = "*";
    set_ships_in_map();
}

void Map::print() const noexcept {
    for (int i = 0; i < height; i++){
        for (int j = 0; j < distance; j++){
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Map::set_ships_in_map() noexcept {
    auto t_conv = table_convoy->get_table();
    auto t_pir = table_pirate->get_table();
        for (auto const &i: t_conv) {
            map[i.second.coord.y][i.second.coord.x] = i.second.ship->get_name();
        }
        for (auto const &j: t_pir) {
            map[j.second.coord.y][j.second.coord.x] = j.second.ship->get_name();
        }
}

void Map::clear_ships_in_map() noexcept {
    auto t_conv = table_convoy->get_table();
    auto t_pir = table_pirate->get_table();
    for (auto const &i : t_conv){
        map[i.second.coord.y][i.second.coord.x] = " ";
    }
    for (auto const &j : t_pir){
        map[j.second.coord.y][j.second.coord.x] = " ";
    }
}


// --------- Конструкторы/деструкторы/сеттеры/геттеры ---------------

Mission::Mission() : money(0), max_weight(0){
    std::random_device rd;
    std::mt19937 mersenne(rd());

    table_pirate = new Table;
    table_convoy = new Table;
    base.at(0).x = 0;
    base.at(0).y = Map::get_height()/2;
    base.at(1).x = Map::get_distance()-1;
    base.at(1).y = Map::get_height()/2;
    base_pirate.x = static_cast<int>(mersenne()%(base.at(1).x-50) + 50);
    base_pirate.y = static_cast<int>(mersenne()%Map::get_height());
    set_pirates();
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
            insert_pirate(DESTROYER, "1", SMALL, SMALL, SMALL, SMALL);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(LCRUISER, "2", SMALL, MEDIUM, MEDIUM, BIG);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(HCRUISER, "3", MEDIUM, MEDIUM, MEDIUM, BIG);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(LCRUISER, "4", MEDIUM, MEDIUM, MEDIUM, SMALL);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(DESTROYER, "5", SMALL, SMALL, SMALL, SMALL);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(BATTLESHIP, "6", BIG, BIG, MEDIUM, SMALL);
        }catch (std::invalid_argument const &err) {
            throw err;
        }
        try{
            insert_pirate(DESTROYER, "7", SMALL, SMALL, SMALL, SMALL);
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
    try{
        std::shared_ptr<Ship> sp = std::make_shared<BattleShip>(type, name, wp1, wp2, wp3, wp4);
        return get_pirate_table()->insert(sp, base_pirate.x, base_pirate.y);
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
    try{
        unsigned long id = get_convoy_table()->insert(std::make_shared<BattleShip>(type, name, wp1, wp2, wp3, wp4), base[0].x, base[0].y);
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
    if (weight_ < 0){
        throw std::length_error("Введено отрицательное число!");
    }
    if (weight + weight_ > max_weight){
        throw std::out_of_range("Слишком большой груз!");
    }
    try{
        unsigned long id = get_convoy_table()->insert(std::make_shared<TransportShip>(name, weight_), base[0].x, base[0].y);
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
    if (weight_ < 0){
        throw std::length_error("Введено отрицательное число!");
    }
    if (weight + weight_ > max_weight){
        throw std::out_of_range("Слишком большой груз!");
    }
    try{
        unsigned long id = get_convoy_table()->insert(std::make_shared<BattleTransport>(name, wp1, wp2, wp3, wp4, weight_), base[0].x, base[0].y);
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
    if (weight_ < 0){ // отрицательное значение или потенциально слишком большое
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
void Mission::upload_automatically(int weight_) { // подгрузка кораблей
    std::shared_ptr<Ship> transport = get_ship_type_info(TRANSPORT);
    std::shared_ptr<Ship> battle_transport = get_ship_type_info(BATTLETRANSPORT);
    try {
        if ((number_convoy_transport() * transport->get_max_weight()) + (number_convoy_battle_transport() * battle_transport->get_max_weight()) < weight_){
            throw std::invalid_argument("too low ships");
        }
        int f = transport->get_max_weight()/battle_transport->get_max_weight() + 1;
        int g = 1;
        if (number_convoy_transport() != 0){
            g = number_convoy_transport();
        }
        int k = (weight_/ (f * (number_convoy_transport() + number_convoy_battle_transport()))) * (number_convoy_battle_transport()/g); // 1/5 часть среднего распределения (общее распределение на 4 конвоя 1 военный транспорт)
        int weight_max_ = 0;
        if (g != 0){
            weight_max_ = (weight_ - k * number_convoy_battle_transport())/g;
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


unsigned long Mission::get_pirate_id(const std::string &name_ship) const {
    return table_pirate->get_id(name_ship);
}

unsigned long Mission::get_convoy_id(const std::string &name_ship) const {
    return table_convoy->get_id(name_ship);
}

double Mission::get_convoy_speed() const noexcept {
    return table_convoy->get_speed_table();
}

void Mission::convoy_finish(unsigned long const &id_) {
    try{
        weight = get_convoy(id_)->get_weight();
        table_convoy->erase(id_);
        weight_delivered += weight;
    }catch (std::invalid_argument const &err){
        std::cout << "Такого корабля в таблице нет!" << std::endl;
    }
}

std::vector<std::pair<unsigned long, int>>* Mission::find_to_shoot(const unsigned long &id) const noexcept {
    auto table_pir = get_pirate_table()->get_table();
    Element sh = get_convoy_table()->find_element(id);
    double displacement;
    int sum_damage = 0;
    auto data = new std::vector<std::pair<unsigned long, int>>;
    for (auto const &i : table_pir){
        displacement = sqrt(pow(sh.coord.x - i.second.coord.x, 2) + pow(sh.coord.y - i.second.coord.y, 2));
        std::array<Weapon, 4> wp = sh.ship->get_wp();
        for (int j = 0; j < 4; j++){
            if (wp[j].get_range() >= displacement){
                sum_damage += wp[j].shoot_test();
            }
        }
        data->push_back(std::make_pair(i.first, sum_damage)); // закидываем в вектор id пирата + потенциальный урон
        sum_damage = 0;
    }
    return data;
}

void Mission::shoot(const unsigned long &id_from, const unsigned long &id_to) noexcept {
    Element convoy = get_convoy_table()->find_element(id_from);
    Element pirate = get_pirate_table()->find_element(id_to);
    int sum_damage = 0;
    std::array<Weapon, 4> wp = convoy.ship->get_wp();
    double displacement = sqrt(pow(convoy.coord.x - pirate.coord.x, 2) + pow(convoy.coord.y - pirate.coord.y, 2));
    for (int i = 0; i < 4; i++){
        if (wp[i].get_range() >= displacement){
            sum_damage += wp[i].shoot();
        }
    }
    get_pirate(id_to)->take_damage(sum_damage);
    if (get_pirate(id_to)->get_hp() <= 0){
        erase_pirate(id_to);
    }
}

void Mission::shoot_pirate(const unsigned long &id_from, const unsigned long &id_to) noexcept {
    Element pirate = get_pirate_table()->find_element(id_from);
    Element convoy = get_convoy_table()->find_element(id_to);
    int sum_damage = 0;
    std::array<Weapon, 4> wp = pirate.ship->get_wp();
    double displacement = sqrt(pow(convoy.coord.x - pirate.coord.x, 2) + pow(convoy.coord.y - pirate.coord.y, 2));
    for (int i = 0; i < 4; i++){
        if (wp[i].get_range() >= displacement){
            sum_damage += wp[i].shoot();
        }
    }
    get_convoy(id_to)->take_damage(sum_damage);
    if (get_convoy(id_to)->get_hp() <= 0){
        erase_convoy(id_to);
    }
}