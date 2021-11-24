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
    int get_money() const noexcept{return money;}
    int get_spent_money() const noexcept {return spent_money;}
    int get_weight() const noexcept {return weight;}
    int get_weight_lost() const noexcept {return weight_lost;}
    int get_max_weight() const noexcept {return max_weight;}
    // -------------------------
    std::shared_ptr<Ship> get_pirate(unsigned long const &id) const; // получить указатель на корабль пиратов
    std::shared_ptr<Ship> get_convoy(unsigned long const &id) const; // получить указатель на корабль конвоя
    // внести в таблицу новый корабль пиратов
    unsigned long insert_pirate(ShipType type, std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4) const;
    // купить военный корабль конвоя
    unsigned long buy_convoy_battle(ShipType type, std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4);
    // купить транспортный корабль
    unsigned long buy_convoy_transport(std::string const &name, int weight_);
    // купить военный транспорт
    unsigned long buy_convoy_battle_transport(std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4, int weight_);
    void sell_convoy(unsigned long const &id); // продать корабль конвоя
    void erase_pirate(unsigned long const &id) const; // уничтожить пиратский корабль
    void erase_convoy(unsigned long const &id); // уничтожить корабль конвоя
    unsigned long count_pirates() const noexcept; // кол-во кораблей пиратов
    unsigned long count_convoy() const noexcept; // кол-во кораблей конвоя
    void buy_weapon(unsigned long const &id, WeaponName type_, int number); // покупка вооружения
    void sell_weapon(unsigned long const &id, int number); // продажа вооружения
    void upload_weight(unsigned long const &id, int weight_); // загрузка корабля
    void unload_weight(unsigned long const &id, int weight_); // разгрузка корабля
    void upload_automatically(); // автоматическая загрузка
    int number_convoy_transport(); // кол-во транспортных кораблей
    int number_convoy_battle_transport(); // кол-во военного транспорта
private:
    Table *table_convoy; // таблица конвоя
    Table *table_pirate; // таблица пиратов
    int const money; // выделенные деньги
    int spent_money; // потраченные деньги
    int weight; // общий вес груза
    int const max_weight; // вес, который нужно довести
    int weight_delivered; // доставленный груз
    int weight_lost; // потерянный груз
    int max_convoy; // макс кол-во кораблей конвоя
    int max_pirate; // макс кол-во кораблей пиратов
    std::array<Coord, 2> base; // базы конвоя
    std::vector<Coord> base_pirate; // базы пиратов

    void set_pirates() const;
};

#endif //LAB4_MISSION_H
