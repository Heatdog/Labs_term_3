//
// Created by User on 07.11.2021.
//

#ifndef LAB4_MISSION_H
#define LAB4_MISSION_H

#include "Table.h"

class Mission{
public:
    Mission();
    ~Mission();
    // ------- Геттеры ---------
    Table *get_pirate_table() const noexcept {return table_pirate;}
    Table* get_convoy_table() const noexcept {return table_convoy;}
    // -------------------------
    std::shared_ptr<Ship> get_pirate(std::string const &name) const noexcept; // получить указатель на корабль пиратов
    std::shared_ptr<Ship> get_convoy(std::string const &name) const noexcept; // получить указатель на корабль конвоя
    // внести в таблицу новый корабль пиратов
    bool insert_pirate(ShipType type, std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4) const noexcept;
    // добавление военного корабля конвоя
    bool insert_convoy_battle(ShipType type, std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4);
    // добавление транспортного корабля
    bool insert_convoy_transport(std::string const &name, int weight_);
    // добавление военного транспорта
    bool insert_convoy_battle_transport(std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4, int weight_);
    bool erase_pirate(std::string const &name) const; // удалить пиратский корабль
    bool erase_convoy(std::string const &name) const; // удалить корабль конвоя
    unsigned long count_pirates() const noexcept; // кол-во кораблей пиратов
    unsigned long count_convoy() const noexcept; // кол-во кораблей конвоя
    bool buy_weapon(std::string const &name_, WeaponName type_, int number); // покупка вооружения
    bool sell_weapon(std::string const &name, int number); // продажа вооружения
private:
    Table *table_convoy; // таблица конвоя
    Table *table_pirate; // таблица пиратов
    int money; // выделенные деньги
    int spent_money; // потраченные деньги
    int weight; // общий вес груза
    int max_weight; // вес, который нужно довести
    int weight_delivered; // доставленный груз
    int weight_lost; // потерянный груз
    int max_convoy = 10; // макс кол-во кораблей конвоя
    int max_pirate = 10; // макс кол-во кораблей пиратов
    std::array<Coord, 2> base; // базы конвоя
    std::vector<Coord> base_pirate; // базы пиратов

    void set_pirates();
};

#endif //LAB4_MISSION_H
