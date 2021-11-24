//
// Created by User on 06.11.2021.
//

#include "Table.h"

// ---------- Элемент -----------
unsigned long Element::current_id = 1;

Element::Element(std::shared_ptr<Ship> ship_) noexcept {
    ship = std::move(ship_);
    coord.x = 0;
    coord.y = 0;
    id = current_id++;
}

// ---------- Таблица -------------

unsigned long Table::insert(std::shared_ptr<Ship> ship) {
    Element el(std::move(ship));
    if (!table.emplace(std::make_pair(el.get_id(), el)).second){
        throw std::invalid_argument("Insertion!");
    }
    return el.get_id();
}

void Table::erase(unsigned long const &id) {
    unsigned long x = table.erase(id);
    if (x > 1){
        throw std::invalid_argument("Erasing! Too many elements");
    } else if (x == 0){
        throw std::invalid_argument("Erasing! Can`t find element");
    }
}

std::shared_ptr<Ship> Table::find(unsigned long const &id) const{
    auto i = table.find(id);
    if (i == table.end()){
        throw std::invalid_argument("Can`t find element!");
    }
    return i->second.ship;
}

unsigned long Table::count() const noexcept {
    return table.size();
}

int Table::count_transport() const noexcept{
    int x = 0;
    for (auto const &i : table){
        if (i.second.ship->get_type() == TRANSPORT){
            x++;
        }
    }
    return x;
}

int Table::count_battle_transport() const noexcept {
    int x = 0;
    for (auto const &i : table){
        if (i.second.ship->get_type() == BATTLETRANSPORT){
            x++;
        }
    }
    return x;
}