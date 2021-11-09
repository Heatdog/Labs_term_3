//
// Created by User on 06.11.2021.
//

#include "Table.h"

// ---------- Элемент -----------

Element::Element(std::shared_ptr<Ship> ship_) noexcept {
    ship = std::move(ship_);
    coord.x = 0;
    coord.y = 0;
}

// ---------- Таблица -------------

void Table::insert(std::shared_ptr<Ship> ship) {
    Element el(std::move(ship));
    if (!table.emplace(std::make_pair(el.ship->get_name(), el)).second){
        throw std::invalid_argument("Insertion!");
    }
}

void Table::erase(std::string const &name) {
    unsigned long x = table.erase(name);
    if (x > 1){
        throw std::invalid_argument("Erasing! Too many elements");
    } else if (x == 0){
        throw std::invalid_argument("Erasing! Can`t find element");
    }
}

std::shared_ptr<Ship> Table::find(std::string const &name){
    auto i = table.find(name);
    if (i == table.end()){
        throw std::invalid_argument("Can`t find element!");
    }
    return i->second.ship;
}

unsigned long Table::count() noexcept {
    return table.size();
}
