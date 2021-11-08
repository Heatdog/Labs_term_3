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

bool Table::insert(std::shared_ptr<Ship> ship) noexcept {
    Element el(std::move(ship));
    return table.emplace(std::make_pair(el.ship->get_name(), el)).second;
}

unsigned long Table::erase(std::string const &name) noexcept {
    return table.erase(name);
}

std::shared_ptr<Ship> Table::find(std::string const &name) noexcept {
    auto i = table.find(name);
    return i == table.end() ? nullptr : i->second.ship;
}

unsigned long Table::count() noexcept {
    return table.size();
}
