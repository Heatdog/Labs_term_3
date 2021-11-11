//
// Created by User on 06.11.2021.
//

#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

#include "Ship.h"
#include <unordered_map>

struct Coord{
    int x;
    int y;
};

struct Element{
    explicit Element(std::shared_ptr<Ship> ship_) noexcept;
    std::shared_ptr<Ship> ship;
    Coord coord{};
};

class Table{
private:
    std::unordered_map<std::string, Element> table;
public:
    explicit Table() = default;
    void insert(std::shared_ptr<Ship> ship);
    void erase(std::string const &name);
    std::shared_ptr<Ship> find(std::string const &name) const;
    int count_transport() const noexcept;
    int count_battle_transport() const noexcept;
    unsigned long count() const noexcept;
    auto get_table() const noexcept {return table;}
};

#endif //LAB4_TABLE_H
