//
// Created by User on 18.12.2021.
//

#include "Console.h"

App::App() noexcept {
    int lev;
    std::string const error = "Ошибка ввода!";
    std::cout << "Добро пожаловать в игру про военный коновой!/n Выберите уровень сложности:\n1) Легкий\n2) Средний\n3) Сложный\n";
    do{
    lev = enter_int();
    if (lev < 1 || lev > 3){
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << error << std::endl;
    } else{
        if (lev == 1){
            level = L_EASY;
        }
        if (lev == 2){
            level = L_MEDIUM;
        }
        if (lev == 3){
            level = L_HARD;
        }
        break;
    }
    } while (true);
    if (level == L_EASY){
        mission.set_dop(100000, 100);
    }
    if (level == L_MEDIUM){
        mission.set_dop(80000, 140);
    }
    if (level == L_HARD){
        mission.set_dop(50000, 210);
    }
}

void App::buy() noexcept{
    int result;
    int ptr;
    std::cout << "Сейчас вы можете купить и продать корабли и вооружение перед заданием" << std::endl;
    std::string menu[] = {"0) Закончить и перейти к распределению груза", "1) Купить корабль", "2) Купить вооружение", "3) Продать корабль", "4) Продать вооружение", "5) Вывести список кораблей"};
    do{
        std::cout << "Текущее количество денег: " << mission.get_money() - mission.get_spent_money() << std::endl;
        if (mission.get_max_weight() - mission.get_weight() > 0){
            ptr = mission.get_max_weight() - mission.get_weight();
        } else{
            ptr = 0;
        }
        std::cout << "Груз необходимый для распределения: " << ptr << std::endl;
        std::cout << "Общее количество загруженного груза: " << mission.get_weight() << std::endl;
        for (std::string const &i : menu){
            std::cout << i << std::endl;
        }
        std::cout << "Введите: " << std::endl;
        result = enter_int();
        if (result == 0){
            break;
        } else if (result == 1){
            buy_convoy();
        } else if (result == 2){
            buy_weapon();
        } else if (result == 3){
            sell_convoy();
        } else if (result == 4){
            sell_weapon();
        } else{
            print_all_convoy();
        }
    } while (true);
}

void App::buy_convoy() noexcept{
    std::string ships[] = {"0) Выход", "1) Транспортный корабль", "2) Военный транспорт", "3) Эсминец",
                           "4) Легкий крейсер", "5) Тяжелый крейсер", "6) Линкор"};
    int result;
    int choose;
    int weight;
    std::string name;
    std::array<WeaponName, 4> list_of_weapons = {UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED};
    std::cout << "Введите: " << std::endl;
    std::cout << "Выберете корабль для покупки" << std::endl;
    for (std::string const &i: ships) {
        std::cout << i << std::endl;
    }
    std::cout << "Введите: " << std::endl;
    result = enter_int();
    if (result == 1){
        print_info_ship(TRANSPORT);
    } else if (result == 2){
        print_info_ship(BATTLETRANSPORT);
    }else if (result == 3){
        print_info_ship(DESTROYER);
    }else if (result == 4){
        print_info_ship(LCRUISER);
    } else if (result == 5){
        print_info_ship(HCRUISER);
    } else if (result == 6){
        print_info_ship(BATTLESHIP);
    } else{
        return;
    }
    std::cout << "Вы уверены в покупке? \n 1) Да \n 2) Нет" << std::endl;
    choose = enter_int();
    if (choose == 1) {
        std::cout << "Ведите название корабля" << std::endl;
        std::cin >> name;
        if (result == 1 || result == 2){
            std::cout << "Введите груз" << std::endl;
            weight = enter_int();
        }
        if (result > 1 && result < 7){
            std::cout << "Выберете вооружение на корабль" << std::endl;
            for (int i = 0; i < 4; i++){
                list_of_weapons[i] = select_weapon();
            }
        }
        if (result == 1){
            try{
                mission.buy_convoy_transport(name, weight);
            }catch (std::range_error const &err1){
                std::cout << "Корабль не был куплен! Слишком много кораблей!" << std::endl;
            }catch (std::overflow_error const &err3){
                std::cout << "Корабль не был куплен! Корабль слишком дорогой!" << std::endl;
            }catch (std::runtime_error const &err4){
                std::cout << "Корабль не был куплен! Имя уже занято" << std::endl;
            }
        } else if (result == 2){
            try{
                mission.buy_convoy_battle_transport(name, list_of_weapons[0], list_of_weapons[1], list_of_weapons[2], list_of_weapons[3], weight);
            }catch (std::range_error const &err1){
                std::cout << "Корабль не был куплен! Слишком много кораблей!" << std::endl;
            }catch (std::overflow_error const &err3){
                std::cout << "Корабль не был куплен! Корабль слишком дорогой!" << std::endl;
            }catch (std::runtime_error const &err4){
                std::cout << "Корабль не был куплен! Имя уже занято" << std::endl;
            }
        }else if (result > 2 && result < 7){
            ShipType type_;
            if (result == 3){
                type_ = DESTROYER;
            }else if (result == 4){
                type_ = LCRUISER;
            } else if (result == 5){
                type_ = HCRUISER;
            } else{
                type_ = BATTLESHIP;
            }
            try{
                mission.buy_convoy_battle(type_, name, list_of_weapons[0], list_of_weapons[1], list_of_weapons[2], list_of_weapons[3]);
            }catch (std::range_error const &err1) {
                std::cout << "Корабль не был куплен! Слишком много кораблей!" << std::endl;
            }catch (std::overflow_error const &err3){
                std::cout << "Корабль не был куплен! Корабль слишком дорогой!" << std::endl;
            }catch (std::runtime_error const &err4){
                std::cout << "Корабль не был куплен! Имя уже занято" << std::endl;
            }
        }
    }
}

void App::print_info_ship(ShipType type_) noexcept {
    auto sh = get_ship_type_info(type_);
    std::cout << "Цена корабля: " << sh->get_price() << std::endl;
    std::cout << "Максимально перевозимый груз: " << sh->get_max_weight() << std::endl;
    std::cout << "Максимальная скорость корабля: " << sh->get_max_speed() << std::endl;
    std::cout << "Количество здоровья: " << sh->get_max_hp() << std::endl;
}

void App::print_info_weapon(WeaponName type_) noexcept {
    auto data = set_weapon();
    for (auto const &i : data){
        if (i.get_name() == type_){
            std::cout << "Цена вооружения: " << i.get_price() << std::endl;
            std::cout << "Урон за выстрел: " << i.get_damage() << std::endl;
            std::cout << "Скорострельность: " << i.get_rate() << std::endl;
            std::cout << "Боезапас: " << i.get_max_ammo() << std::endl;
        }
    }
}

int App::enter_int() noexcept {
    int result = 0;
    std::string const error = "Ошибка ввода!";
    do{
        if (!(std::cin >> result)) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << error << std::endl;
        } else{
            break;
        }
    } while (true);
    return result;
}

void App::buy_weapon() noexcept {
    std::string name;
    int result;
    unsigned long id;
    std::cout << "Введите имя корабля для установки вооружения" << std::endl;
    std::cin >> name;
    try{
        id = mission.get_convoy_id(name);
    }catch (std::invalid_argument const &err){
        std::cout << "Корабля с таким именем нет!" << std::endl;
        return;
    }
    WeaponName wp = select_weapon();
    std::cout << "Введите место установки (от 1 до 4): ";
    result = enter_int();
    try{
        mission.buy_weapon(id, wp, result);
    }catch (std::overflow_error const &err1){
        std::cout << "Орудие не было установлено! Недостаточно денег" << std::endl;
    }catch (std::out_of_range const &err2){
        std::cout << "Орудие не было установлено! Неправильно указано место установки" << std::endl;
    }catch (std::invalid_argument const &err3){
        std::cout << "Орудие не было установлено! Корабль не был найден" << std::endl;
    }
}

WeaponName App::select_weapon() noexcept {
    std::string weapon[] = {"0) Не устанавливать", "1) Малокалиберная пушка", "2) Среднекалиберная пушка", "3) Крупнокалиберная пушка"};
    int result, choose;
    for (std::string const &i : weapon){
        std::cout << i << std::endl;
    }
    std::cout << "Введите номер вооружение, которое хотите купить" << std::endl;
    result = enter_int();
    if (result == 0){
        return UNDEFINED;
    } else if (result == 1){
        print_info_weapon(SMALL);
        std::cout << "Вы уверены в покупке? \n 1) Да \n 2) Нет" << std::endl;
            choose = enter_int();
            if (choose == 1) {return SMALL;
            }
    } else if (result == 2){
        print_info_weapon(MEDIUM);
        std::cout << "Вы уверены в покупке? \n 1) Да \n 2) Нет" << std::endl;
        choose = enter_int();
        if (choose == 1) {
            return MEDIUM;
        }
    } else{
        print_info_weapon(BIG);
        std::cout << "Вы уверены в покупке? \n 1) Да \n 2) Нет" << std::endl;
        choose = enter_int();
        if (choose == 1) {
            return BIG;
        }
    }
    return UNDEFINED;
}

void App::sell_convoy() noexcept {
    std::string name;
    unsigned long id;
    std::cout << "Введите название корабля" << std::endl;
    std::cin >> name;
    try{
        id = mission.get_convoy_id(name);
    }catch (std::invalid_argument const &err){
        std::cout << "Корабль с данным именем не был найден!" << std::endl;
        return;
    }
    mission.sell_convoy(id);
}

void App::sell_weapon() noexcept {
    std::string name;
    unsigned long id;
    int place;
    std::cout << "Введите название корабля" << std::endl;
    std::cin >> name;
    try{
        id = mission.get_convoy_id(name);
    }catch (std::invalid_argument const &err){
        std::cout << "Корабль с данным именем не был найден!" << std::endl;
        return;
    }
    std::cout << "Введите место удаления оружия (1-4)" << std::endl;
    place = enter_int();
    try {
        mission.sell_weapon(id, place);
    }catch (std::out_of_range const &err){
        std::cout << "Неправильно указано место удаления" << std::endl;
    }
}

bool App::upload() noexcept {
    int result, weight, ptr;
    std::string name;
    unsigned long id;
    std::cout << "На этом этапе вы можете загрузить и разгрузить груз по кораблям" << std::endl;
    do {
        std::cout << "Нажмите 0, если хотите закончить и начать вылазку" << std::endl;
        std::cout << "Нажмите 1, если хотите автоматической загрузки с максимальной скоростью конвоя" << std::endl;
        std::cout << "Нажмите 2, если хотите вручную загрузить корабли" << std::endl;
        std::cout << "Нажмите 3, если хотите разгрузить выбранный корабль" << std::endl;
        std::cout << "Нажмите 4, чтобы вывести список кораблей" << std::endl;
        std::cout << "Нажмите 5, если хотите вернуться в магазин" << std::endl;
        if (mission.get_max_weight() - mission.get_weight() > 0){
            ptr = mission.get_max_weight() - mission.get_weight();
        } else{
            ptr = 0;
        }
        std::cout << "Осталось распределить: " << ptr << std::endl;
        std::cout << "Общий вес груза : " << mission.get_weight() << std::endl;
        std::cout << "Текущая скорость конвоя: " << mission.get_convoy_speed() << std::endl;
        result = enter_int();
        if (result == 0){
            if (mission.get_max_weight() - mission.get_weight() > 0){
                std::cout << "Вы не полностью распределили груз!" << std::endl;
            } else{
                break;
            }
        }else if (result == 1) {
            try {
                mission.upload_automatically();
            } catch (std::invalid_argument const &err) {
                std::cout << "Слишком мало кораблей! Докупите еще" << std::endl;
            }
        } else if (result == 2) {
            std::cout << "Введите название транспортного корабля" << std::endl;
            std::cin >> name;
            try{
                id = mission.get_convoy_id(name);
            }catch (std::invalid_argument const &err1){
                std::cout << "Данный корабль не был найден" << std::endl;
                continue;
            }
            std::cout << "Доступное количество загружаемого груза на данный корабль: " << mission.get_convoy(id)->get_max_weight() - mission.get_convoy(id)->get_weight() << std::endl;
            std::cout << "Введите количество загружаемого груза" << std::endl;
            weight = enter_int();
            try {
                mission.upload_weight(id, weight);
            }catch (std::invalid_argument const &err1){
                std::cout << "Слишком большое значение веса или отрицательное значение веса" << std::endl;
            }
        } else if (result == 3){
            std::cout << "Введите название транспортного корабля" << std::endl;
            std::cin >> name;
            try{
                id = mission.get_convoy_id(name);
            }catch (std::invalid_argument const &err1){
                std::cout << "Данный корабль не был найден" << std::endl;
                continue;
            }
            std::cout << "Текущий груз на данном корабле: " << mission.get_convoy(id)->get_weight() << std::endl;
            std::cout << "Введите кол-во груза, которое вы хотите разгрузить" << std::endl;
            weight = enter_int();
            try{
                mission.unload_weight(id, weight);
            }catch (std::invalid_argument const &err){
                std::cout << "Неправильно указан формат веса или ввели слишком большое значение" << std::endl;
            }
        } else if (result == 4){
            print_all_convoy();
        }else{
            break;
        }
    } while (true);
    if (result == 5){
        return false;
    }
    return true;
}

void App::print_all_convoy() const noexcept {
    auto table = mission.get_convoy_table()->get_table();
    if (table.empty()){
        std::cout << "Список кораблей пуст!" << std::endl;
    } else {
        for (auto const &i: table) {
            std::cout << "Название: " << i.second.ship->get_name() << "\t Тип корабля: ";
            i.second.ship->print_type();
            std::cout << "\t Скорость: " << i.second.ship->get_speed();
            std::cout << "\t Здоровье: " << i.second.ship->get_hp();
            if (i.second.ship->get_type() == TRANSPORT || i.second.ship->get_type() == BATTLETRANSPORT) {
                std::cout << "\t Вес: " << i.second.ship->get_weight() << "\t Макс вес: "
                          << i.second.ship->get_max_weight();
            }
            if (i.second.ship->get_type() != TRANSPORT) {
                for (int k = 0; k < 4; k++) {
                    std::cout << "\t" << k + 1 << " орудие: ";
                    i.second.ship->get_weapons(k+1).print_type();
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void App::gameplay() noexcept {
    std::string menu[] = {"1) Вправо", "2) Влево", "3) Вверх", "4) Вниз", "5) Выстрелить"};
    int result;
    Map map(mission.get_pirate_base().x, mission.get_pirate_base().y, mission.get_convoy_table(), mission.get_pirate_table());
    map.print();
    // сразу управлять можно, имея 5 вариаций - вперед, назад, вправо, влево, выстрелять
    do{
        std::cout << "Текущее состояние конвоя" << std::endl;
        print_all_convoy();
        std::cout << "Выберете действие для конвоя" << std::endl;
        for (std::string const &k : menu){
            std::cout << k << std::endl;
        }
        result = enter_int();
        map.clear_ships_in_map();
        if (result == 1){
            displace(1, 0);
        } else if (result == 2){
            displace(-1, 0);
        } else if (result == 3){
            displace(0, -1);
        }else if (result == 4){
            displace(0, 1);
        } else if (result == 5){
            shoot();
            displace(1, 0);
        }
        bot_turn();
        map.set_ships_in_map();
        map.print();
        if (mission.get_weight_delivered() >= mission.get_max_weight()){
            std::cout << "Вы выиграли!!!" << std::endl;
            break;
        }
        if (mission.get_weight_lost() >= mission.get_max_weight()){
            std::cout << "Вы проиграли!" << std::endl;
            std::cout << "Выжившие корабли" << std::endl;
            print_all_convoy();
            break;
        }

    } while (true);
}

void App::displace(int x_, int y_) noexcept {
    int velocity = static_cast<int>(mission.get_convoy_speed()); // из-за размерности карты
    auto table = mission.get_convoy_table()->get_table();
    auto table_ms = mission.get_convoy_table();
    for (auto &i : table){
        table_ms->push_new_coord(i.first, i.second.coord.x + x_ * velocity, i.second.coord.y + (y_ * velocity)/3);
        i.second.coord.x += x_ * velocity;
        i.second.coord.y += (y_ * velocity)/3;
        if (i.second.coord.x < 0){
            table_ms->push_new_coord(i.first, 0, i.second.coord.y);
        }
        if (i.second.coord.x > Map::get_distance()-1){
            table_ms->push_new_coord(i.first, Map::get_distance()-1, i.second.coord.y);
        }
        if (i.second.coord.y < 1){
            table_ms->push_new_coord(i.first, i.second.coord.x, 1);
        }
        if (i.second.coord.y > Map::get_height()-1){
            table_ms->push_new_coord(i.first, i.second.coord.x, Map::get_height()-2);
        }
        if (i.second.coord.x >= mission.get_convoy_finish().x-1 && i.second.coord.y < mission.get_convoy_finish().y + 2 && i.second.coord.y > mission.get_convoy_finish().y - 2){
            mission.convoy_finish(i.first);
        }
    }
}

void App::shoot() noexcept {
    auto table = mission.get_convoy_table()->get_table();
    unsigned long result;
    std::string name;
    bool flag = false;
    std::vector<std::pair<unsigned long , int>>* data;
    for (auto &i : table){
        std::cout << "Сейчас стреляет корабль " << i.second.ship->get_name() << std::endl;
        std::cout << "Доступна стрельба по кораблям пиратов: " << std::endl;
        data = mission.find_to_shoot(i.first);
        for (auto const &j : *data){
            auto pirate = mission.get_pirate(j.first);
            if (j.second != 0){
                std::cout << "Имя: " << pirate->get_name() << "\t Тип: ";
                pirate->print_type();
                std::cout << "\t Текущее здоровье: " << pirate->get_hp() << "\t Урон по кораблю: " << j.second << std::endl;
                flag = true;
            }
        }
        if (flag){
            std::cout << "Выберете корабль, по которому будете стрелять" << std::endl;
            std::cin >> name;
            try{
                result = mission.get_pirate_id(name);
                mission.shoot(i.first, result);
            }catch (std::invalid_argument const &err){
                std::cout << "Такого корабля нет!" << std::endl;
            }
        } else{
            std::cout << "Ни один корабль пиратов не находится в досягаемости!" << std::endl;
        }
        flag = false;
        delete data;
    }
}


