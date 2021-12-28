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
    } else if (type == TRANSPORT){
        return "transport";
    } else if (type == BATTLETRANSPORT){
        return "battle transport";
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
            sell_convoy(window);
        } else if (result == 4){
            sell_weapon(window);
        } else if (result == 5){
            print_all_convoy(window);
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
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
    Map_Window fon;
    sf::Font font;
    font.loadFromFile("../Images/PFAgoraSlabProBold.ttf");
    sf::Vector2f centerPos = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    sf::Text text("Enter name of ship in console", font, 50);
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

    std::string name;
    int result;
    unsigned long id;
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

        std::cout << "Enter name" << std::endl;
        std::cin >> name;
        break;
    }
    try{
        id = mission.get_convoy_id(name);
    }catch (std::invalid_argument const &err){
        while (window->isOpen()){
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }
            text.setString("We can`t find this ship!" );
            text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
        return;
    }
    if (mission.get_convoy(id)->get_type() == TRANSPORT){
        while (window->isOpen()){
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }
            text.setString("We can`t insert weapon on this ship!" );
            text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
        return;
    }
    WeaponName wp;
    bool flag = true;
    try{
        while (window->isOpen()){
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }

            if (flag) {
                text.setString("Enter place \n 1 \n 2 \n 3 \n 4");
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                    wp = select_weapon(window, 0);
                    mission.buy_weapon(id, wp, 1);
                    flag = false;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                    wp = select_weapon(window, 1);
                    mission.buy_weapon(id, wp, 2);
                    flag = false;
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                    wp = select_weapon(window, 2);
                    mission.buy_weapon(id, wp, 3);
                    flag = false;
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                    wp = select_weapon(window, 3);
                    mission.buy_weapon(id, wp, 4);
                    flag = false;
                }
            } else{
                auto sh = mission.get_convoy(id);
                text.setString("The weapon was successfully installed on the ship! \n Name: " + sh->get_name()
                               + "\n Type: " + string_ship(sh->get_type()) + "\n First weapon: " + string_weapon(sh->get_weapons(1).get_name())
                               + "\n Second weapon: " + string_weapon(sh->get_weapons(2).get_name()) +
                               "\n Third weapon: " + string_weapon(sh->get_weapons(3).get_name()) +
                               "\n Fourth weapon: " + string_weapon(sh->get_weapons(4).get_name()));
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
            }

            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
    }catch (std::overflow_error const &err1){
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
            text.setString("The gun was not installed! Not enough money");
            text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
    }catch (std::out_of_range const &err2){
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
            text.setString("The gun was not installed! Place!");
            text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
    }catch (std::invalid_argument const &err3){
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
            text.setString("The gun was not installed! Can`t find");
            text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
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

void App::sell_convoy(sf::RenderWindow* window) noexcept {
    Map_Window fon;
    sf::Font font;

    font.loadFromFile("../Images/PFAgoraSlabProBold.ttf");
    sf::Vector2f centerPos = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    sf::Text text("Enter name in console", font, 50);
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
    std::string name;
    unsigned long id;
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

        std::cout << "Enter name" << std::endl;
        std::cin >> name;
        break;
    }
    try{
        id = mission.get_convoy_id(name);
        text.setString("Convoy successfully removed!");
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }
            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }

    }catch (std::invalid_argument const &err){
        text.setString("Can`t find ship!");
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }
            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
        return;
    }
    mission.sell_convoy(id);
}

void App::sell_weapon(sf::RenderWindow* window) noexcept {
    Map_Window fon;
    sf::Font font;
    std::string name;
    unsigned long id;
    int place;

    font.loadFromFile("../Images/PFAgoraSlabProBold.ttf");
    sf::Vector2f centerPos = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    sf::Text text("Enter name of ship in console", font, 50);
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

        std::cout << "Enter name of ship" << std::endl;
        std::cin >> name;
        break;
    }
    try{
        id = mission.get_convoy_id(name);
        auto sh = mission.get_convoy(id);
        text.setString("Convoy successfully found!\n First weapon: " + string_weapon(sh->get_wp().at(0).get_name())
        + "\n Second weapon: " + string_weapon(sh->get_wp().at(1).get_name()) + "\n Third weapon: " + string_weapon(sh->get_wp().at(2).get_name())
        + "\n Fourth weapon: " + string_weapon(sh->get_wp().at(3).get_name()));
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }
            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
    }catch (std::invalid_argument const &err){
        text.setString("Can`t find ship!");
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }
            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
        return;
    }
    text.setString("Enter place of erasing weapon: \n 1 \n 2 \n 3 \n 4");
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
            place = 1;
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            place = 2;
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
            place = 3;
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
            place = 4;
            break;
        }
        window->clear();
        window->draw(fon.sprite);
        window->draw(text);
        window->display();
    }
    try {
        mission.sell_weapon(id, place);
        text.setString("Weapon successfully removed!");
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }
            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }

    }catch (std::out_of_range const &err){
        text.setString("Dismiss in place of weapon!");
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }
            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
    }
}

bool App::upload(sf::RenderWindow* window) noexcept {
    int result, weight, ptr;
    std::string name;
    int weight_aut;
    unsigned long id;

    Map_Window fon;
    sf::Font font;
    std::string rt = "Here you can upload and unload ships \n 0) Go to next step \n 1) Automatic loading "
                     "\n 2) Manually load the ships \n 3) Unload the selected ship \n 4) Display a list of ships";
    std::string wd;

    font.loadFromFile("../Images/PFAgoraSlabProBold.ttf");
    sf::Vector2f centerPos = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    sf::Text text(wd, font, 50);


        while (window->isOpen()){
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
            }
            if (mission.get_max_weight() - mission.get_weight() > 0){
                ptr = mission.get_max_weight() - mission.get_weight();
            } else{
                ptr = 0;
            }
            wd += rt;
            wd += "\n It remains to distribute: " + std::to_string(ptr) + "\n Total weight of the cargo: " +
                    std::to_string(mission.get_weight()) + "\n Current speed of the convoy: " +
                    std::to_string(mission.get_convoy_speed());
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                wd = "Enter the weight (in console) \n";
                text.setString(wd);
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
                std::cout << "enter weight: " << std::endl;
                weight_aut = enter_int();
                if (weight_aut < 0){
                    while (window->isOpen()){
                        sf::Event event;
                        while (window->pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window->close();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                window->close();
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                            break;
                        }
                        text.setString("You entered a negative number!");
                        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                        window->clear();
                        window->draw(fon.sprite);
                        window->draw(text);
                        window->display();
                    }
                } else {
                    try {
                        mission.upload_automatically(weight_aut);
                        while (window->isOpen()){
                            sf::Event event;
                            while (window->pollEvent(event)) {
                                if (event.type == sf::Event::Closed)
                                    window->close();
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                    window->close();
                                }
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                                break;
                            }
                            text.setString("Automatic upload successfully completed!");
                            text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                            window->clear();
                            window->draw(fon.sprite);
                            window->draw(text);
                            window->display();
                        }
                    } catch (std::invalid_argument const &err) {
                        while (window->isOpen()){
                            sf::Event event;
                            while (window->pollEvent(event)) {
                                if (event.type == sf::Event::Closed)
                                    window->close();
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                    window->close();
                                }
                            }

                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                                break;
                            }
                            text.setString("Too few ships! Buy more");
                            text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                            window->clear();
                            window->draw(fon.sprite);
                            window->draw(text);
                            window->display();
                        }
                    }
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                wd = "Enter the name of the transport ship (in console)";
                text.setString(wd);
                text.setCharacterSize(30);
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
                wd = "";
                std::cout << "Enter the name of the transport ship" << std::endl;
                std::cin >> name;
                try{
                    id = mission.get_convoy_id(name);
                    while (window->isOpen()){
                        sf::Event event;
                        while (window->pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window->close();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                window->close();
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                            break;
                        }
                        text.setString("The ship was successfully found!");
                        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                        window->clear();
                        window->draw(fon.sprite);
                        window->draw(text);
                        window->display();
                    }
                }catch (std::invalid_argument const &err1){
                    while (window->isOpen()){
                        sf::Event event;
                        while (window->pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window->close();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                window->close();
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                            break;
                        }
                        text.setString("This ship was not found!");
                        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                        window->clear();
                        window->draw(fon.sprite);
                        window->draw(text);
                        window->display();
                    }
                    continue;
                }
                wd += "\n The available amount of loaded cargo on this ship: " + std::to_string(mission.get_convoy(id)->get_max_weight() - mission.get_convoy(id)->get_weight()) + "\n"
                        + "Enter the quantity of the loaded cargo (in console)\n";
                text.setString(wd);
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
                text.setCharacterSize(30);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
                std::cout << "Enter the quantity of the loaded cargo" << std::endl;
                weight = enter_int();
                try {
                    mission.upload_weight(id, weight);
                    while (window->isOpen()){
                        sf::Event event;
                        while (window->pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window->close();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                window->close();
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                            break;
                        }
                        text.setString("The ship was successfully uploaded!");
                        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                        window->clear();
                        window->draw(fon.sprite);
                        window->draw(text);
                        window->display();
                    }
                }catch (std::invalid_argument const &err1){
                    while (window->isOpen()){
                        sf::Event event;
                        while (window->pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window->close();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                window->close();
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                            break;
                        }
                        text.setString("Too much weight value or negative weight value!");
                        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                        window->clear();
                        window->draw(fon.sprite);
                        window->draw(text);
                        window->display();
                    }
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                wd = "Enter the name of the transport ship (in console)";
                text.setString(wd);
                text.setCharacterSize(30);
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
                wd = "";
                std::cin >> name;
                try{
                    id = mission.get_convoy_id(name);
                    while (window->isOpen()){
                        sf::Event event;
                        while (window->pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window->close();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                window->close();
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                            break;
                        }
                        text.setString("The ship was successfully found!");
                        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                        window->clear();
                        window->draw(fon.sprite);
                        window->draw(text);
                        window->display();
                    }
                }catch (std::invalid_argument const &err1){
                    while (window->isOpen()){
                        sf::Event event;
                        while (window->pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window->close();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                window->close();
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                            break;
                        }
                        text.setString("This ship was not found!");
                        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                        window->clear();
                        window->draw(fon.sprite);
                        window->draw(text);
                        window->display();
                    }
                    continue;
                }
                wd += "\n Current cargo on this ship: " + std::to_string(mission.get_convoy(id)->get_weight()) + "\n"
                      + "Enter the quantity of cargo you want to unload (in console)\n";
                text.setString(wd);
                text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                window->clear();
                window->draw(fon.sprite);
                window->draw(text);
                window->display();
                std::cout << "Enter the quantity of cargo you want to unload" << std::endl;
                weight = enter_int();
                try{
                    mission.unload_weight(id, weight);
                    while (window->isOpen()){
                        sf::Event event;
                        while (window->pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window->close();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                window->close();
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                            break;
                        }
                        text.setString("The ship was successfully unloaded!");
                        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                        window->clear();
                        window->draw(fon.sprite);
                        window->draw(text);
                        window->display();
                    }
                }   catch (std::invalid_argument const &err){
                    while (window->isOpen()){
                        sf::Event event;
                        while (window->pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window->close();
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                                window->close();
                            }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                            break;
                        }
                        text.setString("The weight format is incorrectly specified or the value is too large!");
                        text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

                        window->clear();
                        window->draw(fon.sprite);
                        window->draw(text);
                        window->display();
                    }
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
                print_all_convoy(window);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
                break;
            }
            text.setString(wd);
            text.setCharacterSize(50);
            text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
            wd = "";
        }
}

void App::print_all_convoy(sf::RenderWindow* window) const noexcept {
    Map_Window fon;
    sf::Font font;

    font.loadFromFile("../Images/PFAgoraSlabProBold.ttf");
    sf::Vector2f centerPos = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    sf::Text text("", font, 20);
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);


    if (mission.count_convoy() == 0){
        text.setString("The list of ships is empty!");
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }
            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
        }
    } else {
        std::string ptr = "";
        auto table = mission.get_convoy_table()->get_table();
        while (window->isOpen()){
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                break;
            }

            for (auto const &i: table) {
                ptr.append("Name: " + i.second.ship->get_name() + " \t Type of ship: " + string_ship(i.second.ship->get_type()) +
                        " \t Speed: " + std::to_string((int)i.second.ship->get_speed()) + "\t HP: " + std::to_string(i.second.ship->get_hp()));
                if (i.second.ship->get_type() == TRANSPORT || i.second.ship->get_type() == BATTLETRANSPORT) {
                    ptr.append(" \t Weight: " + std::to_string(i.second.ship->get_weight()) + " \t Max weight: " +
                            std::to_string(i.second.ship->get_max_weight()));
                }
                if (i.second.ship->get_type() != TRANSPORT) {
                    for (int k = 0; k < 4; k++) {
                        ptr.append("\t" + std::to_string(k+1) + " wp: " + string_weapon(i.second.ship->get_weapons(k + 1).get_name()));
                    }
                }
                ptr.append(" \n");
            }
            text.setString(ptr);
            text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
            window->clear();
            window->draw(fon.sprite);
            window->draw(text);
            window->display();
            ptr = "";
            text.setString(ptr);
        }
    }
}

void App::gameplay(sf::RenderWindow* window) noexcept {
    sf::Font font;
    bool flag = true;
    font.loadFromFile("../Images/PFAgoraSlabProBold.ttf");
    sf::Vector2f centerPos = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    sf::Text text("", font, 30);

    float heroteleporttimer = 0; //создаем для примера телепортации героя через 3 секунды
    sf::Clock clock; //создаем переменную времени, т.о. привязка ко времени(а не мощности/загруженности процессора)

    int result;
    Map map(mission.get_pirate_base().x, mission.get_pirate_base().y, mission.get_convoy_table(), mission.get_pirate_table());
    while (window->isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time/800; //скорость игры

        heroteleporttimer += time;

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
            }
        }

        if (flag &&  heroteleporttimer > 100) {
            heroteleporttimer = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                displace(1, 0);
                shoot();
                flag = false;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                displace(-1, 0);
                shoot();
                flag = false;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                displace(0, -1);
                shoot();
                flag = false;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                displace(0, 1);
                shoot();
                flag = false;
            }

            if (mission.get_weight_delivered() >= mission.get_max_weight() || mission.count_pirates() == 0) {
                std::string final;
                if (mission.count_pirates() == 0) {
                    final = "All the pirate ships have been destroyed!";
                } else {
                    final = "You delivered " + std::to_string(mission.get_weight_delivered()) + " amount of weight \n";
                }
                while (window->isOpen()) {
                    sf::Event event;
                    while (window->pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window->close();
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                            window->close();
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
                        break;
                    }

                    text.setString("You`re win!!! \n" + final);
                    text.setFillColor(sf::Color::Red);
                    text.setCharacterSize(60);
                    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2,
                                     centerPos.y - text.getGlobalBounds().height / 2);
                    window->clear();
                    window->draw(map.sprite);
                    for (auto &i : mission.get_convoy_table()->get_table()){
                        i.second.ship->sprite.setPosition(i.second.coord.x* 10, i.second.coord.y* 10);
                        window->draw(i.second.ship->sprite);
                    }
                    for (auto &j : mission.get_pirate_table()->get_table()){
                        j.second.ship->sprite.setPosition(j.second.coord.x* 10, j.second.coord.y* 10);
                        window->draw(j.second.ship->sprite);
                    }
                    window->draw(text);
                    window->display();
                }
                break;
            }
            window->clear();
            window->draw(map.sprite);
            for (auto &i : mission.get_convoy_table()->get_table()){
                i.second.ship->sprite.setPosition(i.second.coord.x * 10, i.second.coord.y * 10);
                window->draw(i.second.ship->sprite);
            }
            for (auto &j : mission.get_pirate_table()->get_table()){
                j.second.ship->sprite.setPosition(j.second.coord.x * 10, j.second.coord.y * 10);
                window->draw(j.second.ship->sprite);
            }
            window->draw(text);
            window->display();
        } else if (heroteleporttimer > 100){
            heroteleporttimer = 0;
            bot_turn();


            if (mission.get_weight() < mission.get_max_weight()) {
                while (window->isOpen()) {
                    sf::Event event;
                    while (window->pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window->close();
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                            window->close();
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
                        break;
                    }

                    text.setString("You`re lose!");
                    text.setFillColor(sf::Color::Red);
                    text.setCharacterSize(90);
                    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2,
                                     centerPos.y - text.getGlobalBounds().height / 2);
                    window->clear();
                    window->draw(map.sprite);
                    for (auto &i : mission.get_convoy_table()->get_table()){
                        i.second.ship->sprite.setPosition(i.second.coord.x * 10, i.second.coord.y * 10);
                        window->draw(i.second.ship->sprite);
                    }
                    for (auto &j : mission.get_pirate_table()->get_table()){
                        j.second.ship->sprite.setPosition(j.second.coord.x * 10, j.second.coord.y * 10);
                        window->draw(j.second.ship->sprite);
                    }
                    window->draw(text);
                    window->display();
                }
                break;
            }

            window->clear();
            window->draw(map.sprite);
            for (auto &i : mission.get_convoy_table()->get_table()){
                i.second.ship->sprite.setPosition(i.second.coord.x * 10, i.second.coord.y * 10);
                window->draw(i.second.ship->sprite);
            }
            for (auto &j : mission.get_pirate_table()->get_table()){
                j.second.ship->sprite.setPosition(j.second.coord.x * 10, j.second.coord.y * 10);
                window->draw(j.second.ship->sprite);
            }
            window->draw(text);
            window->display();
            flag = true;
        }
    }
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
        auto table_pirate = mission.get_pirate_table()->get_table();
        auto table_convoy = mission.get_convoy_table()->get_table();

        unsigned long count_pirate = mission.count_pirates();
        if (count_pirate == 0){
            return;
        }
        for (auto &j : table_convoy){
            if (j.second.ship->get_type() != TRANSPORT) {
                if (mission.count_pirates() == 0) {
                    return;
                }
                mission.shoot(j.first, table_pirate.begin()->first);
            }
        }
    }
}


