#include "Console.h"

void game() noexcept {
    /*App start;
    do{
        start.buy();
    } while (!start.upload());
    start.gameplay();*/
}

int main() {
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1300, 800), "Game");

    //BattleShip ship(DESTROYER, "A", SMALL, SMALL, SMALL, SMALL);
    //ship.sprite.setPosition(50, 25);

    sf::Clock clock;

    Map_Window fon;
    sf::Font font;
    Level level;
    font.loadFromFile("../Images/PFAgoraSlabProBold.ttf");

    bool flag = true;

    sf::Text text("", font, 50);
    text.setString("Select level:\n1) Easy\n2) Medium\n3) Hard\n");
    sf::Vector2f centerPos = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

    while (window->isOpen() && flag) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            level = L_EASY;
            flag = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            level = L_MEDIUM;
            flag = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            level = L_HARD;
            flag = false;
        }
        window->clear();

        window->draw(fon.sprite);
        window->draw(text);

        window->display();
    }

    App start(level);
    text.setString("0) Next step \n 1) Buy new ship \n 2) Buy weapon \n 3) Sell ship \n 4) Sell weapon \n 5) Print list of ships");
    text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);

    sf::Text text_money("", font, 35);
    text_money.setPosition(10, 10);

    sf::Text text_cargo("", font, 35);
    text_cargo.setPosition(10, 60);

    sf::Text text_cargo_uploaded("", font, 35);
    text_cargo_uploaded.setPosition(10, 110);

    int ptr;

    std::string info_ship;
    sf::Text text_info_ship("", font, 50);


    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            start.buy_convoy(window);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            start.buy_weapon(window);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
            start.sell_convoy(window);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            start.sell_weapon(window);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
            start.print_all_convoy(window);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
            break;
        }
        text_money.setString("Current money: " + std::to_string(start.mission.get_money() - start.mission.get_spent_money()));
        if (start.mission.get_max_weight() - start.mission.get_weight() > 0){
            ptr = start.mission.get_max_weight() - start.mission.get_weight();
        } else{
            ptr = 0;
        }
        text_cargo.setString("Cargo, needed to upload: " + std::to_string(ptr));
        text_cargo_uploaded.setString("Amount of uploaded cargo: " + std::to_string(start.mission.get_weight()));



        window->clear();

        window->draw(fon.sprite);
        window->draw(text);
        window->draw(text_money);
        window->draw(text_cargo);
        window->draw(text_cargo_uploaded);

        window->display();
    }

    start.upload(window);
    start.gameplay(window);

    delete window;
    return 0;
}