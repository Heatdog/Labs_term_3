//
// Created by User on 31.10.2021.
//

#ifndef LAB4_SHIP_H
#define LAB4_SHIP_H

/*!
 * \file
 * \brief Заголовочный файл с описанием классов кораблей
 */

#include <utility>
#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>

//! Набор возможных типов вооружения
enum WeaponName{
    UNDEFINED, ///< Неопределенный тип оружия
    BIG, ///< Крупное вооружение
    MEDIUM, ///< Среднее вооружение
    SMALL, ///< Малое вооружение
};

//! Набор возможных типов кораблей
enum ShipType{
    UNDEFINEDSHIP, ///< неопределенный тип
    TRANSPORT, ///< транспортный корабль
    BATTLETRANSPORT, ///< военный транспорт
    DESTROYER, ///< эсминец
    LCRUISER, ///< легкий крейсер
    HCRUISER, ///< тяжелый крейсер
    BATTLESHIP, ///< линкор
};

//! Набор возможных званий капитанов
enum RangType{
    LIEUTENANT, ///< Лейтенант
    MAJOR, ///< Майор
    ADMIRAL, ///< Адмирал
};

/*!
 * В классе храниться информация об имени и о звании
 * \brief Класс капитана
 */
struct Capitan{
    Capitan() noexcept : name(""), rang(LIEUTENANT) {};
    explicit Capitan(std::string name_, RangType rang_) noexcept : name(std::move(name_)), rang(rang_){}
    Capitan(Capitan const &a) = default;
    Capitan& operator=(Capitan const &a);
    std::string name; ///< имя
    RangType rang; ///< звание
};

/*!
 * В классе храниться информация об оружии: тип, урон за выстрел, скорострельность, дальность, боекомплект и цена
 * \brief Класс вооружения
 */
class Weapon{
public:
    Weapon() noexcept;
    explicit Weapon(WeaponName name_, int damage_, int rate_, double range_, int max_ammo_, int ammo_, int price_);
    Weapon(Weapon const &a) = default;
    Weapon& operator=(Weapon const &a);

    /*!
     * урон складывается как скорострельность * урон с учетом текущего боезапаса. При недостатке боезапаса будет возвращен 0
     * \brief выстрелить
     *  \param[in] none
     * \return количество урона
    */
    int shoot() noexcept; // выстрелить
    int shoot_test() const noexcept;

    // ----------------- Геттеры-----------
    /*!
     * \brief геттер имени
     *  \param[in] none
     * \return имя
    */
    WeaponName get_name() const noexcept{return name;}

    /*!
     * \brief геттер дальности стрельбы
     *  \param[in] none
     * \return дальность
    */
    double get_range() const noexcept{return range;}

    /*!
     * \brief геттер урона
     *  \param[in] none
     * \return урон
    */
    int get_damage() const noexcept{return damage;}

    /*!
     * \brief геттер скорострельности
     *  \param[in] none
     * \return скорострельность
    */
    int get_rate() const noexcept{return rate;}

    /*!
     * \brief геттер максимального боезапаса
     *  \param[in] none
     * \return максимальный боезапас
    */
    int get_max_ammo() const noexcept{return max_ammo;}

    /*!
     * \brief геттер боезапаса
     *  \param[in] none
     * \return боезапас
    */
    int get_ammo() const noexcept{return ammo;}

    /*!
     * \brief геттер цены
     *  \param[in] none
     * \return цену за оружие
    */
    int get_price() const noexcept{return price;}
    void print_type() const noexcept;
    //-------------------------------------------

private:
    WeaponName name; ///< Имя оружия
    int damage; ///< урон
    int rate; ///< скорострельность
    double range; ///< дальность
    int max_ammo; ///< макс боекомплект
    int ammo; ///< текущий боекомплект
    int price; ///< цена
};


/*!
 * Базовый класс корабля, от него наследуются все остальные типы. В классе храниться информация об корабле, поля которых
 * общие как для боевого, так и для транспортного корабля.
 * \brief Класс корабля
 */
class Ship{
public:
    Ship() noexcept;
    explicit Ship(ShipType type_, std::string name, Capitan const &capitan_, double speed_, double max_speed_,
                  int hp, int max_hp_, int price);
    Ship(Ship const &a) = default;
    Ship& operator=(Ship const &a);

    // ------------ Геттеры --------------
    /*!
     * \brief получение типа
     *  \param[in] none
     * \return тип корабля
    */
    ShipType get_type() const noexcept{return type;}
    /*!
     * \brief получение имени корабля
     *  \param[in] none
     * \return имя корабля
    */
    std::string get_name() const noexcept{return name;}
    /*!
     * \brief получение капитана
     *  \param[in] none
     * \return копию корабля
    */
    Capitan get_cap() const noexcept{return capitan;}
    /*!
     * \brief получение текущей скорости
     *  \param[in] none
     * \return скорость корабля
    */
    double get_speed() const noexcept{return speed;}
    /*!
     * \brief получение максимальной скорости корабля
     *  \param[in] none
     * \return максимальная скорость
    */
    double get_max_speed() const noexcept{return max_speed;}
    /*!
     * \brief получение текущего хп
     *  \param[in] none
     * \return хп
    */
    int get_hp() const noexcept{return hp;}
    /*!
     * \brief получение максимального количества корабля
     *  \param[in] none
     * \return максимальное хп
    */
    int get_max_hp() const noexcept{return max_hp;};
    /*!
     * \brief получение цены корабля
     *  \param[in] none
     * \return цена
    */
    int get_price() const noexcept{return price;}
    // ----------------

    // ------------ Сеттеры----------
    /*!
     * \brief установление типа корабля
     *  \param[in] ShipType - тип корабля
     * \return none
    */
    void set_type(ShipType type_) noexcept{type = type_;}
    /*!
     * \brief установление скорости корабля
     *  \param[in] speed_ - скорость корабля
     * \return none
     * \throw invalid_argument - если скорость меньше нуля или больше максимальной
    */
    void set_speed(double speed_);
    /*!
     * \brief установление имени корабля
     *  \param[in] name_ - имя корабля
     * \return none
    */
    void set_name(std::string const &name_) noexcept {name = name_;}
    /*!
     * \brief установление капитана корабля
     *  \param[in] cap_ - капитан
     * \return none
    */
    void set_cap(Capitan const &cap_) noexcept {capitan = cap_;}
    /*!
     * \brief установление максимальной скорости корабля
     *  \param[in] max_speed_ - макс скорость
     * \return none
     * \throw invalid_argument - если значение меньше нуля или меньше текущей скорости
    */
    void set_max_speed(double max_speed_);
    /*!
     * \brief установление текущего хп корабля
     *  \param[in] hp_ - хп
     * \return none
     * \throw invalid_argument - если hp_ < 0
    */
    void set_hp(int hp_);
    /*!
     * \brief установление максимального хп корабля
     *  \param[in] hp_ - хп
     * \return none
     * \throw invalid_argument - если hp_ < 0
    */
    void set_max_hp(int hp_);
    /*!
     * \brief установление текущего цены корабля
     *  \param[in] price_ - цена
     * \return none
     * \throw invalid_argument - если price_ < 0
    */
    void set_price(int price_);
    //-----------------

    /*!
     * \brief получение урона и уменьшение hp на значение damage
     *  \param[in] damage - урон от попадания
     * \return none
     * \throw invalid_argument - если передали значение меньше нуля
    */
    void take_damage(int damage);

    /*!
     * \brief увеличение цены
     *  \param[in] price_ - цена, на которую хоти увеличить
     * \return none
    */
    void increase_price(int price_) noexcept;

    void print_type() const noexcept;
    //-------- Виртуальные методы для переопределения -------------
    /*!
     * \brief получение текущего веса
     *  \param[in] none
     * \return текущий вес груза
    */
    virtual int get_weight() const noexcept {return 0;}

    /*!
    * \brief получение максимально возможного груза
    *  \param[in] none
    * \return максимально возможный груз
   */
    virtual int get_max_weight() const noexcept {return 0;}

    /*!
    * \brief получение коэффициента скорости
    *  \param[in] none
    * \return коэффициент скорости
   */
    virtual double get_ratio() const noexcept {return 0;};

    /*!
    * \brief получение оружия на данном месте корабля
    *  \param[in] number - место оружия на корабле
    * \return копия оружия
     * \throw out_of_range - если number < 1 или > 4
   */
    virtual Weapon get_weapons(int number) const {return {};};

    /*!
    * \brief получение массива всех установленных пушек на данном корабле
    *  \param[in] none
    * \return массив array[4] с вооружением
   */
    virtual std::array<Weapon, 4> get_wp() const noexcept {return {};};

    /*!
    * \brief модифицирование вооружение
    *  \param[in] number - место установки
     *  \param[in]  weapon - имя нового оружия
    * \return массив array[4] с вооружением
     * \throw out_of_range - если number < 1 или > 4
   */
    virtual void modify_weapon(int number, WeaponName weapon){};

    /*!
    * \brief добавление веса
    * \param[in] number - количество веса
    * \return none
    * \throw invalid_argument - если number превышает максимальный груз
   */
    virtual void add_weight(int number){};
    //---------------------------------------------------------
    std::string file;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;


private:
    ShipType type; ///< тип корабля
    std::string name; ///< имя
    Capitan capitan; ///< капитан
    double speed; ///< скорость
    double max_speed; ///< макс скорость
    int hp; ///< хп
    int max_hp; ///< макс хп
    int price; ///< цена
};


/*!
 * \brief Класс транспортного корабля
 */
class TransportShip : public Ship{
public:
    TransportShip() noexcept;
    explicit TransportShip(std::string const &name, Capitan const &capitan_, double speed_, double max_speed_,
                           int hp_, int max_hp_, int price_, int weight_, int max_weight_);
    explicit TransportShip(std::string const &name, int weight);
    TransportShip(TransportShip const &a) = default;
    TransportShip& operator=(TransportShip const &a) = default;

    // ------------------ Геттеры ---------------
    int get_weight() const noexcept override{return weight;}
    int get_max_weight() const noexcept override{return max_weight;}
    double get_ratio() const noexcept override{return ratio;}
    void add_weight(int amount) override;
    //---------------------------

    /*!
    * \brief получение максимального груза
    *  \param[in] weight - вес
    * \return none
     * \throw invalid_argument - если вес меньше нуля
   */
    void set_max_weight(int weight); // установить макс вес
    /*!
    * \brief получение скорость при выбранной нагрузке
    *  \param[in] weight_ - вес
    * \return скорости при выбранной нагрузке
     * \throw invalid_argument - если вес меньше нуля
   */
    double new_max_speed(int weight_);
    /*!
    * \brief установление коэффициента скорости
    *  \param[in] rat_ - коэффициент
    * \return none
     * \throw invalid_argument - если rat_ меньше 0 или больше 1
   */
    void set_ratio(double rat_);
    /*!
    * \brief установление веса
    *  \param[in] amount - вес
    * \return none
     * \throw invalid_argument - если вес меньше нуля
   */
    void set_weight(int amount);

private:
    int weight; ///< масса текущего груза
    int max_weight; ///< макс масса груза
    double ratio; ///< коэффициент скорости в зависимости от массы груза
};

/*!
 * \brief Класс военного корабля
 */
class BattleShip : public Ship{
public:
    BattleShip() noexcept;
    explicit BattleShip(ShipType type, std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
                        int hp_, int max_hp_, int price_, std::array<Weapon, 4> weapons_);
    explicit BattleShip(ShipType type, std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
                        int hp_, int max_hp_, int price_);
    explicit BattleShip(ShipType type_, std::string const &name_, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4);
    BattleShip(BattleShip const &a) = default;
    BattleShip& operator=(BattleShip const &a) = default;

    // --------- Сеттеры --------------------
    /*!
    * \brief установление орудия на данное место
    *  \param[in] wp - орудие
     *  \param[in] number - место установки
    * \return none
     * \throw invalid_argument - если number < 1 || > 4
   */
    void set_weapons(Weapon const &wp, int number){weapons.at(number-1) = wp;}
    // -------------------------------------

    // ---------- Переопределенные методы ----------------------
    Weapon get_weapons(int number) const override{return weapons.at(number-1);}
    std::array<Weapon, 4> get_wp() const noexcept override{return weapons;}
    void modify_weapon(int number, WeaponName weapon) override; // модифицировать вооружение
    // -----------------------------------------

    /*!
    * \brief получение копии орудия в данном месте корабля
     *  \param[in] number - место установки
    * \return орудие
     * \throw invalid_argument - если number < 1 || > 4
   */
    Weapon info_weapon(int number) const; // информация об оружии в данном участке корабля
    /*!
    * \brief выстрел по данной координате
     *  \param[in] x - x-координата
     *  \param[in] y - y-координата
    * \return общий урон орудий, которые достают до данного места
   */
private:
    std::array<Weapon, 4> weapons; ///< массив орудий на корабле
};

/*!
 * \brief Класс военного транспорта
 */
class BattleTransport : public TransportShip{
public:
    BattleTransport() noexcept;
    explicit BattleTransport(std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
                             int hp_, int max_hp_, int price_, int weight_, int max_weight_);
    explicit BattleTransport(std::string const &name_, Capitan const &capitan_, double speed_, double max_speed_,
    int hp_, int max_hp_, int price_, int weight_, int max_weight_, std::array<Weapon, 4> weapons_);
    explicit BattleTransport(std::string const &name_, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4, int weight_);
    BattleTransport(BattleTransport const &a) = default;
    BattleTransport& operator=(BattleTransport const &a) = default;

    //-------------- Сеттеры -------------------
    /*!
   * \brief установление орудия на данное место
   *  \param[in] wp - орудие
    *  \param[in] number - место установки
   * \return none
    * \throw invalid_argument - если number < 1 || > 4
  */
    void set_weapons(Weapon const &wp, int number){weapons.at(number-1) = wp;}
    // ---------------------------------------

    // ----------------- Переопределенные методы -----------------
    Weapon get_weapons(int number) const override{return weapons.at(number-1);}
    std::array<Weapon, 4> get_wp() const noexcept override{return weapons;}
    void modify_weapon(int number, WeaponName weapon) override; // модифицировать вооружение
    // ---------------------------------------

    /*!
    * \brief получение копии орудия в данном месте корабля
     *  \param[in] number - место установки
    * \return орудие
     * \throw invalid_argument - если number < 1 || > 4
   */
    Weapon info_weapon(int number) const; // информация об оружии в данном участке корабля
    /*!
    * \brief выстрел по данной координате
     *  \param[in] x - x-координата
     *  \param[in] y - y-координата
    * \return общий урон орудий, которые достают до данного места
   */
private:
    std::array<Weapon, 4> weapons; ///< массив орудий на корабле
};


// отвечает за магазин вооружения и корпусов ------------------------------
std::vector<Weapon> set_weapon(); // запись возможного вооружения
std::vector<std::shared_ptr<Ship>> set_ships();
std::shared_ptr<Ship> get_ship_type_info(ShipType type_);
//--------------------------------------------------------------------------

namespace Battle{
    template <class T>
    void modify_weapon(T& ship, int number, WeaponName weapon);

    template <class T>
    Weapon info_weapon(T const &ship, int number);
}

#endif //LAB4_SHIP_H
