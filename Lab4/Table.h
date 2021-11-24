//
// Created by User on 06.11.2021.
//

#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

#include "Ship.h"
#include <unordered_map>
#include "UnordedNode.h"

struct Coord{
    int x;
    int y;
};

struct Element{
public:
    explicit Element(std::shared_ptr<Ship> ship_) noexcept;
    std::shared_ptr<Ship> ship;
    Coord coord{};
    unsigned long get_id() const noexcept{return id;}
private:
    unsigned long id;
    static unsigned long current_id;
};

class Table{
private:
    Lab4::unordered_map<unsigned long, Element> table; // строки на id
public:
    explicit Table() = default;
    unsigned long insert(std::shared_ptr<Ship> ship);
    void erase(unsigned long const &id);
    std::shared_ptr<Ship> find(unsigned long const &id) const;
    int count_transport() const noexcept;
    int count_battle_transport() const noexcept;
    unsigned long count() const noexcept;
    auto get_table() const noexcept {return table;}
};

#endif //LAB4_TABLE_H
