//
// Created by User on 18.12.2021.
//

#include "Console.h"

Map_Window::Map_Window() noexcept {
    image.loadFromFile("../Images/WaterImage.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

std::string string_weapon(WeaponName wp){
    if (wp == SMALL){
        return "small";
    } else if (wp == MEDIUM){
        return "medium";
    } else if (wp == BIG){
        return "big";
    } else{
        return "undefined";
    }
}

std::string string_ship(ShipType type){
    if (type == DESTROYER){
        return "destroyer";
    } else if (type == LCRUISER){
        return "light cruiser";
    } else if (type == HCRUISER){
        return "heavy cruiser";
    } else if (type == BATTLESHIP){
        return "battleship";
    }
}

App::App(Level level_) noexcept {
    level = level_;
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

void App::buy(sf::RenderWindow* window) noexcept{
    int result;
    int ptr;
    std::cout << "Now you can buy ships and weapons" << std::endl;
    std::string menu[] = {"Enter any number to go to next step", "Enter 1, to buy ship",
                          "Enter 2, to buy weapon", "Enter 3, to sell ship", "Enter 4, to sell weapon",
                          "Enter 5, to print list of ships"};
    do{
        std::cout << "Amount of money: " << mission.get_money() - mission.get_spent_money() << std::endl;
        if (mission.get_max_weight() - mission.get_weight() > 0){
            ptr = mission.get_max_weight() - mission.get_weight();
        } else{
            ptr = 0;
        }
        std::cout << "Cargo, needed to upload: " << ptr << std::endl;
        std::cout << "Amount of uploaded cargo: " << mission.get_weight() << std::endl;
        for (std::string const &i : menu){
            std::cout << i << std::endl;
        }
        std::cout << "Enter: " << std::endl;
        result = enter_int();
        if (result == 1){
            buy_convoy(window);
        } else if (result == 2){
            buy_weapon(window);
        } else if (result == 3){
            sell_convoy();
        } else if (result == 4){
            sell_weapon();
        } else if (result == 5){
            print_all_convoy();
        } else{
            break;
        }
    } while (true);
}

void App::buy_convoy(sf::RenderWindow* window) noexcept{
    std::string info;
    Map_Window fon;
    sf::Font font;
    int result;
    int choose;
    bool flag = true;
    int weight;
    std::string name;
    std::array<WeaponName, 4> list_of_weapons = {UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED};

    font.loadFromFile("../Images/PFAgoraSlabProBold.ttf");
    sf::Vector2f centerPos = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    sf::Text text("1) Buy transport ship \n 2) Buy battle transport \n 3) Buy destroyer \n 4) Buy light cruiser \n 5) Buy heavy cruiser \n 6) Buy battleship", font, 50);
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
    while (window->isOpen()){
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            result = 1;
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            result = 2;
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            result = 3;
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            result = 4;
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
            result = 5;
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
            result = 6;
            break;
        }
        window->clear();
        window->draw(fon.sprite);
        window->draw(text);
        window->display();
    }
    while (window->isOpen()){
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
            }
        }

        text.setString("Enter all properties of ship in console");
        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

        window->clear();
        window->draw(fon.sprite);
        window->draw(text);
        window->display();

        std::cout << "Enter name of ship" << std::endl;
        std::cin >> name;
        if (result == 1 || result == 2) {
            std::cout << "Enter cargo" << std::endl;
            weight = enter_int();
        }
        if (result > 1 && result < 7) {
            text.setString(info + "\n Enter weapons");
            for (int i = 0; i < 4; i++) {
                list_of_weapons[i] = select_weapon(window, i);
            }
        }
        break;
    }
    if (result == 1){
        try{
            mission.buy_convoy_transport(name, weight);
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                auto sh = mission.get_convoy(mission.get_convoy_id(name));
                text.setString("The ship was successfully included in the convoy! \n Name: " + sh->get_name()
                + "\n Type: Transport \n Max cargo: " + std::to_string(sh->get_weight()) + "\n Max velocity: " +
                                       std::to_string(sh->get_speed()));
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::range_error const &err1){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Too many ships");
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::overflow_error const &err3){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Ship too expensive");
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::runtime_error const &err4){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Name has already selected" );
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::out_of_range const &err3){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Cargo is too big!" );
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::length_error const &err5){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! You enter negative number!" );
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }
    } else if (result == 2){
        try{
            mission.buy_convoy_battle_transport(name, list_of_weapons[0], list_of_weapons[1], list_of_weapons[2], list_of_weapons[3], weight);
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                auto sh = mission.get_convoy(mission.get_convoy_id(name));
                text.setString("The ship was successfully included in the convoy! \n Name: " + sh->get_name()
                               + "\n Type: Battle transport \n Max cargo: " + std::to_string(sh->get_weight()) + "\n Max velocity: " +
                               std::to_string(sh->get_speed()) + "\n First weapon: " + string_weapon(sh->get_weapons(1).get_name())
                               + "\n Second weapon: " + string_weapon(sh->get_weapons(2).get_name()) +
                               "\n Third weapon: " + string_weapon(sh->get_weapons(3).get_name()) +
                               "\n Fourth weapon: " + string_weapon(sh->get_weapons(4).get_name()));

                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::range_error const &err1){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Too many ships");
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::overflow_error const &err3){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Ship too expensive");
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::runtime_error const &err4){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Name has already selected" );
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::out_of_range const &err3){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Cargo is too big!" );
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::length_error const &err5){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! You enter negative number!" );
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
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
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                auto sh = mission.get_convoy(mission.get_convoy_id(name));
                text.setString("The ship was successfully included in the convoy! \n Name: " + sh->get_name()
                               + "\n Type: " + string_ship(sh->get_type()) + "\n Max cargo: " + std::to_string(sh->get_weight()) + "\n Max velocity: " +
                               std::to_string(sh->get_speed()) + "\n First weapon: " + string_weapon(sh->get_weapons(1).get_name())
                               + "\n Second weapon: " + string_weapon(sh->get_weapons(2).get_name()) +
                               "\n Third weapon: " + string_weapon(sh->get_weapons(3).get_name()) +
                               "\n Fourth weapon: " + string_weapon(sh->get_weapons(4).get_name()));

                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::range_error const &err1) {
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Too many ships");
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::overflow_error const &err3){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Ship too expensive");
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }catch (std::runtime_error const &err4){
            while (window->isOpen()){
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    break;
                }
                text.setString("Ship wasn't bought! Name has already selected" );
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
            }
        }
    }
}

std::string App::print_info_ship(ShipType type_, std::string& wd) noexcept {
    auto sh = get_ship_type_info(type_);
    wd = "Price of ship: " + std::to_string(sh->get_price()) + "\n Max cargo: " + std::to_string(sh->get_max_weight()) + "\n Max velocity: " +
            std::to_string(sh->get_max_speed()) + "\n HP: " + std::to_string(sh->get_max_hp());
    return wd;
}

std::string App::print_info_weapon(WeaponName type_, std::string& wd) noexcept {
    auto data = set_weapon();
    for (auto const &i : data){
        if (i.get_name() == type_){
            std::cout << "price of weapon: " << i.get_price() << std::endl;
            std::cout << "Damage: " << i.get_damage() << std::endl;
            std::cout << "Rate: " << i.get_rate() << std::endl;
            std::cout << "Ammo: " << i.get_max_ammo() << std::endl;
        }
    }
}

int App::enter_int() noexcept {
    int result = 0;
    std::string const error = "Error!";
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

void App::buy_weapon(sf::RenderWindow* window) noexcept {
    std::string name;
    int result;
    unsigned long id;
    std::cout << "Enter name of ship" << std::endl;
    std::cin >> name;
    try{
        id = mission.get_convoy_id(name);
    }catch (std::invalid_argument const &err){
        std::cout << "We can`t find this ship!" << std::endl;
        return;
    }
    WeaponName wp = select_weapon(window, 0);
    std::cout << "Enter place (from 1 to 4): ";
    result = enter_int();
    try{
        mission.buy_weapon(id, wp, result);
    }catch (std::overflow_error const &err1){
        std::cout << "The gun was not installed! Not enough money" << std::endl;
    }catch (std::out_of_range const &err2){
        std::cout << "The gun was not installed! Place!" << std::endl;
    }catch (std::invalid_argument const &err3){
        std::cout << "The gun was not installed! Can`t find" << std::endl;
    }
}

WeaponName App::select_weapon(sf::RenderWindow* window, int i) noexcept {
    Map_Window fon;
    sf::Font font;
    int result;
    std::string name;
    font.loadFromFile("../Images/PFAgoraSlabProBold.ttf");
    sf::Vector2f centerPos = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    sf::Text text("install on position " + std::to_string(i+1)+ "\n 0) Not install \n 1) Small - caliber cannon  "
                  "\n 2) Middle - caliber cannon \n 3) Large - caliber gun", font, 50);
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
    while (window->isOpen()){
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
            }
        }

        window->clear();
        window->draw(fon.sprite);
        window->draw(text);

        window->display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
            return SMALL;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            return MEDIUM;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
            return BIG;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
            return UNDEFINED;
        }
    }
}

void App::sell_convoy() noexcept {
    std::string name;
    unsigned long id;
    std::cout << "Enter name" << std::endl;
    std::cin >> name;
    try{
        id = mission.get_convoy_id(name);
    }catch (std::invalid_argument const &err){
        std::cout << "Can`t find ship!" << std::endl;
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
    int weight_aut;
    unsigned long id;
    std::cout << "Here you can upload and unload weapons" << std::endl;
    do {
        std::cout << "Enter any button to go to next step" << std::endl;
        std::cout << "Enter 1, for automatic loading" << std::endl;
        std::cout << "Press 2 if you want to manually load the ships" << std::endl;
        std::cout << "Press 3 if you want to unload the selected ship" << std::endl;
        std::cout << "Press 4 to display a list of ships" << std::endl;
        std::cout << "Press 5 if you want to return to the store" << std::endl;
        if (mission.get_max_weight() - mission.get_weight() > 0){
            ptr = mission.get_max_weight() - mission.get_weight();
        } else{
            ptr = 0;
        }
        std::cout << "It remains to distribute: " << ptr << std::endl;
        std::cout << "Total weight of the cargo: " << mission.get_weight() << std::endl;
        std::cout << "Current speed of the convoy: " << mission.get_convoy_speed() << std::endl;
        result = enter_int();
        if (result == 1) {
            std::cout << "Enter the weight" << std::endl;
            weight_aut = enter_int();
            if (weight_aut < 0){
                std::cout << "You entered a negative number!" << std::endl;
            } else {
                try {
                    mission.upload_automatically(weight_aut);
                } catch (std::invalid_argument const &err) {
                    std::cout << "Too few ships! Buy more" << std::endl;
                }
            }
        } else if (result == 2) {
            std::cout << "Enter the name of the transport ship" << std::endl;
            std::cin >> name;
            try{
                id = mission.get_convoy_id(name);
            }catch (std::invalid_argument const &err1){
                std::cout << "This ship was not found" << std::endl;
                continue;
            }
            std::cout << "The available amount of loaded cargo on this ship: " << mission.get_convoy(id)->get_max_weight() - mission.get_convoy(id)->get_weight() << std::endl;
            std::cout << "Enter the quantity of the loaded cargo" << std::endl;
            weight = enter_int();
            try {
                mission.upload_weight(id, weight);
            }catch (std::invalid_argument const &err1){
                std::cout << "Too much weight value or negative weight value" << std::endl;
            }
        } else if (result == 3){
            std::cout << "Enter the name of the transport ship" << std::endl;
            std::cin >> name;
            try{
                id = mission.get_convoy_id(name);
            }catch (std::invalid_argument const &err1){
                std::cout << "This ship was not found" << std::endl;
                continue;
            }
            std::cout << "Current cargo on this ship: " << mission.get_convoy(id)->get_weight() << std::endl;
            std::cout << "Enter the quantity of cargo you want to unload" << std::endl;
            weight = enter_int();
            try{
                mission.unload_weight(id, weight);
            }catch (std::invalid_argument const &err){
                std::cout << "The weight format is incorrectly specified or the value is too large" << std::endl;
            }
        } else if (result == 4){
            print_all_convoy();
        }else{
            if (mission.get_max_weight() - mission.get_weight() > 0 && result != 5){
                std::cout << "You have not fully distributed the cargo!" << std::endl;
            } else{
                break;
            }
        }
    } while (true);
    if (result == 5){
        return false;
    }
    return true;
}

void App::print_all_convoy() const noexcept {
    if (mission.count_convoy() == 0){
        std::cout << "List of ships let!" << std::endl;
    } else {
        auto table = mission.get_convoy_table()->get_table();
        for (auto const &i: table) {
            std::cout << "Name: " << i.second.ship->get_name() << "\t Type of ship: ";
            i.second.ship->print_type();
            std::cout << "\t Speed: " << i.second.ship->get_speed();
            std::cout << "\t HP: " << i.second.ship->get_hp();
            if (i.second.ship->get_type() == TRANSPORT || i.second.ship->get_type() == BATTLETRANSPORT) {
                std::cout << "\t Weight: " << i.second.ship->get_weight() << "\t Max weight: "
                          << i.second.ship->get_max_weight();
            }
            if (i.second.ship->get_type() != TRANSPORT) {
                for (int k = 0; k < 4; k++) {
                    std::cout << "\t" << k + 1 << " cannon: ";
                    i.second.ship->get_weapons(k + 1).print_type();
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void App::gameplay() noexcept {
    std::string menu[] = {"1) Right", "2) Left", "3) Up", "4) Down"};
    int result;
    Map map(mission.get_pirate_base().x, mission.get_pirate_base().y, mission.get_convoy_table(), mission.get_pirate_table());
    map.print();
    do{
        std::cout << "Текущее состояние конвоя" << std::endl;
        print_all_convoy();
        std::cout << "Choose action" << std::endl;
        for (std::string const &k : menu){
            std::cout << k << std::endl;
        }
        map.clear_ships_in_map();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            displace(1, 0);
            shoot();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            displace(-1, 0);
            shoot();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            displace(0, -1);
            shoot();
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            displace(0, 1);
            shoot();
        }
        bot_turn();
        map.set_ships_in_map();
        map.print();
        if (mission.get_weight_delivered() >= mission.get_max_weight() || mission.count_pirates() == 0){
            std::cout << "Вы выиграли!!!" << std::endl;
            if (mission.count_pirates() == 0){
                std::cout << "Все корабли пиратов уничтожены!" << std::endl;
            } else{
                std::cout << "Вы привезли " << mission.get_weight_delivered() << " груза" << std::endl;
            }
            break;
        }
        if (mission.get_weight() < mission.get_max_weight()){
            std::cout << "Вы проиграли!" << std::endl;
            break;
        }
    } while (true);
}

void App::displace(int x_, int y_) noexcept {
    if (mission.count_convoy() != 0) {
        int velocity = static_cast<int>(mission.get_convoy_speed()); // из-за размерности карты
        auto table = mission.get_convoy_table()->get_table();
        auto table_ms = mission.get_convoy_table();
        for (auto &i: table) {
            table_ms->push_new_coord(i.first, i.second.coord.x + x_ * velocity, i.second.coord.y + (y_ * velocity) / 3);
            i.second.coord.x += x_ * velocity;
            i.second.coord.y += (y_ * velocity) / 3;
            if (i.second.coord.x < 0) {
                table_ms->push_new_coord(i.first, 0, i.second.coord.y);
            }
            if (i.second.coord.x > Map::get_distance() - 1) {
                table_ms->push_new_coord(i.first, Map::get_distance() - 1, i.second.coord.y);
            }
            if (i.second.coord.y < 1) {
                table_ms->push_new_coord(i.first, i.second.coord.x, 1);
            }
            if (i.second.coord.y > Map::get_height() - 1) {
                table_ms->push_new_coord(i.first, i.second.coord.x, Map::get_height() - 2);
            }
            if (i.second.coord.x >= mission.get_convoy_finish().x - 5 && i.second.coord.y <= mission.get_convoy_finish().y + 5 && i.second.coord.y >= mission.get_convoy_finish().y - 5) {
                mission.convoy_finish(i.first);
            } else{
                i.second.ship->sprite.setPosition(static_cast<float>(i.second.coord.x), static_cast<float>(i.second.coord.y));
            }
        }
    }
}

void App::shoot() noexcept {
    if (mission.count_convoy() != 0) {
        auto table = mission.get_convoy_table()->get_table();
        unsigned long result;
        std::string name;
        bool flag = false;
        int count = 0;
        std::vector<std::pair<unsigned long, int>> *data;
        for (auto &i: table) {
            data = mission.find_to_shoot(i.first);
            for (auto const &j: *data) {
                auto pirate = mission.get_pirate(j.first);
                if (j.second != 0) {
                    if (count == 0) {
                        std::cout << "Сейчас стреляет корабль " << i.second.ship->get_name() << std::endl;
                        std::cout << "Доступна стрельба по кораблям пиратов: " << std::endl;
                    }
                    std::cout << "Имя: " << pirate->get_name() << "\t Тип: ";
                    pirate->print_type();
                    std::cout << "\t Текущее здоровье: " << pirate->get_hp() << "\t Урон по кораблю: " << j.second
                              << std::endl;
                    flag = true;
                    count++;
                }
            }
            count = 0;
            if (flag) {
                std::cout << "Выберете корабль, по которому будете стрелять" << std::endl;
                std::cin >> name;
                try {
                    result = mission.get_pirate_id(name);
                    mission.shoot(i.first, result);
                } catch (std::invalid_argument const &err) {
                    std::cout << "Такого корабля нет!" << std::endl;
                }
            }
            flag = false;
            delete data;
        }
    }
}


