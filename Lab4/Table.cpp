//
// Created by User on 06.11.2021.
//

#include "Table.h"

// ---------- Элемент -----------
unsigned long Element::current_id = 1;

Element::Element(std::shared_ptr<Ship> ship_, int x_, int y_) noexcept {
    ship = std::move(ship_);
    coord.x = x_;
    coord.y = y_;
    id = current_id++;
}

// ---------- Таблица -------------

bool Table::find_name(const std::string &name) const noexcept {
    for (auto const &i : table){
        if (i.second.ship->get_name() == name){
            return false;
        }
    }
    return true;
}

unsigned long Table::insert(std::shared_ptr<Ship> ship, int x_, int y_) {
    if (find_name(ship->get_name())){
        Element el(std::move(ship), x_, y_);
        if (!table.emplace(std::make_pair(el.get_id(), el)).second){
            throw std::invalid_argument("Insertion!");
        }
        return el.get_id();
    }
    throw std::runtime_error("Insertion!");
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

Element Table::find_element(unsigned long id) const {
    auto i = table.find(id);
    if (i == table.end()){
        throw std::invalid_argument("Can`t find element!");
    }
    return i->second;
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

unsigned long Table::get_id(std::string const &name_ship) const {
    for (auto const &i : table){
        if (i.second.ship->get_name() == name_ship){
            return i.first;
        }
    }
    throw std::invalid_argument("Can`t find this element!");
}

double Table::get_speed_table() const noexcept {
    double velocity;
    if (count() == 0){
        return 0;
    }
    velocity = table.begin()->second.ship->get_speed();
    for (auto const &i : table){
        if (i.second.ship->get_speed() < velocity){
            velocity = i.second.ship->get_speed();
        }
    }
    return velocity;
}

void Table::push_new_coord(unsigned long id, int x_, int y_) {
    auto i = table.find(id);
    i->second.coord.x = x_;
    i->second.coord.y = y_;
}

int Table::get_damage(const unsigned long &id, int place) noexcept {
    auto sh = find(id);
    int sum = 0;
    if (sh->get_weapons(place).get_rate() > sh->get_weapons(place).get_ammo()){
        sum = sh->get_weapons(place).get_damage() * sh->get_weapons(place).get_ammo();
    }else{
        sum = sh->get_weapons(place).get_damage() * sh->get_weapons(place).get_rate();
    }
    return sum;
}