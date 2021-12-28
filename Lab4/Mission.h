//
// Created by User on 07.11.2021.
//

/*!
 * \file
 * \brief Заголовочный файл с описанием класса миссия
 */

#ifndef LAB4_MISSION_H
#define LAB4_MISSION_H

#include "Table.h"
#include <random>

/*!
 * \brief Класс миссии, основной класс для взаимодействия между консольным приложением и базами данных
 * \warning Обработка исключений, например при невозможности загрузить корабль, лежит на консольном приложении
 *
 * В миссии хранятся 2 таблицы - для пиратов и конвоя. Также в ней содержится информация о бюджете, базах и грузе
 */

class Map{
private:
    static int const height = 80;
    static int const distance = 120;
    std::string map[80][120];
    Table* const table_convoy;
    Table* const table_pirate;
public:
    static int get_height() noexcept{
        return height;
    }
    static int get_distance() noexcept{
        return distance;
    }
    explicit Map(int p_x, int p_y, Table* table_convoy_, Table* table_pirate_) noexcept;
    void print() const noexcept;
    void set_ships_in_map() noexcept;
    void clear_ships_in_map() noexcept;

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};

class Mission{
public:
    Mission();
    ~Mission();

    // ------- Геттеры ---------
    /*!
     * \defgroup getters Геттеры класса Mission
     * \brief Данный модуль предназначен для геттеров класса Mission
     * @{
     */

    /*!
     * \brief Получение указателя на таблицу пиратов
     * \param[in] none
     * \return Указатель на таблицу пиратов
     */
    Table *get_pirate_table() const noexcept {return table_pirate;}

    /*!
     * \brief Получение указателя на таблицу конвоя
     * \param[in] none
     * \return Указатель на таблицу конвоя
     */
    Table* get_convoy_table() const noexcept {return table_convoy;}

    /*!
     * \brief Получение кол-ва выделенных на миссию денег
     * \param[in] none
     * \return int значение кол-ва выделенных на миссию денег
     */
    int get_money() const noexcept{return money;}

    /*!
    * \brief Получение кол-ва потраченных денег
    * \param[in] none
    * \return int значение кол-ва потраченных денег
    * @return
    */
    int get_spent_money() const noexcept {return spent_money;}

    /*!
    * \brief Получение кол-ва загруженного груза на всех кораблях конвоя
    * \param[in] none
    * \return int значение кол-ва загруженного груза на всех кораблях конвоя
    * @return
    */
    int get_weight() const noexcept {return weight;}

    /*!
    * \brief Получение кол-ва потерянного груза в результате конвоирования
    * \param[in] none
    * \return int значение кол-ва потерянного груза в результате конвоирования
    * @return
    */
    int get_weight_lost() const noexcept {return weight_lost;}

    /*!
   * \brief Получение кол-ва необходимого к доставке груза
   * \param[in] none
   * \return int значение кол-ва необходимого к доставке груза
   * @return
   */
    int get_max_weight() const noexcept {return max_weight;}
    // -------------------------
    /*!
   * \brief Получение указатель на корабль пиратов
   * \param[in] id - id корабля пиратов
   * \return std::shared_ptr на корабль пиратов с данным id
   * \throw invalid_argument если не нашли корабль пиратов с данным id
   * @return
   */
    std::shared_ptr<Ship> get_pirate(unsigned long const &id) const;

    /*!
   * \brief Получение указатель на корабль конвоя
   * \param[in] id - id корабля пиратов
   * \return std::shared_ptr на корабль конвоя с данным id
   * \throw invalid_argument если не нашли корабль с данным id
   */
    std::shared_ptr<Ship> get_convoy(unsigned long const &id) const;
    /*!
     * @}
     */

    /*!
     * \defgroup insert Добавление кораблей
     * \brief Данный модуль предназначен для включения кораблей пиратов и конвоя в соответствующие таблицы
     * @{
     */

    /*!
     * Метод создает корабль пиратов с выбранным вооружением, при этом цена корабля никак не учитывается, т.к. нет лимита на деньги у пиратов
     * Также id элемента создается в самом методе, и пользователь никак не может повлиять на id
   * \brief Включение в таблицу пиратов нового корабля
   * \param[in] type - тип корабля
   * \param[in] name - имя корабля
   * \param[in] wp1 - название первого оружия
     * \param[in] wp2 - название второго оружия
     * \param[in] wp3 - название третьего оружия
     * \param[in] wp4 - название четвертого оружия
   * \return id включенного корабля
   * \throw range_error если мы превысили лимит кол-ва кораблей
     * \throw invalid_argument если уже существует корабль с данным id
   */
    unsigned long insert_pirate(ShipType type, std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4) const;

    /*!
     * Метод создает военный корабль с выбранным вооружением, при этом цена корабля учитывается, и при большой цене будет вызвано исключение
     * Также id элемента создается в самом методе, и пользователь никак не может повлиять на id
   * \brief Покупка и включение в таблицу конвоя нового военного корабля
   * \param[in] type - тип корабля
   * \param[in] name - имя корабля
   * \param[in] wp1 - название первого оружия
     * \param[in] wp2 - название второго оружия
     * \param[in] wp3 - название третьего оружия
     * \param[in] wp4 - название четвертого оружия
   * \return id включенного корабля
   * \throw range_error если мы превысили лимит кол-ва кораблей
     * \throw invalid_argument если уже существует корабль с данным id
     * \throw overflow_error если мы потратили слишком много денег и превысили лимит
   */
    unsigned long buy_convoy_battle(ShipType type, std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4);

    /*!
     * Метод создает транспортный корабль с выбранным весом груза, при этом цена корабля учитывается, и при большой цене будет вызвано исключение
     * Также id элемента создается в самом методе, и пользователь никак не может повлиять на id
   * \brief Покупка и включение в таблицу конвоя нового транспортного корабля
   * \param[in] name - имя корабля
   * \param[in] weight_ - загруженный на данный корабль вес
   * \return id включенного корабля
   * \throw range_error если мы превысили лимит кол-ва кораблей
     * \throw invalid_argument если уже существует корабль с данным id или мы загрузили слишком большой груз на этот корабль
     * \throw overflow_error если мы потратили слишком много денег и превысили лимит
   */
    unsigned long buy_convoy_transport(std::string const &name, int weight_);

    /*!
     * Метод создает военно-транспортный корабль с выбранным весом груза и вооружением, при этом цена корабля учитывается, и при большой цене будет вызвано исключение
     * Также id элемента создается в самом методе, и пользователь никак не может повлиять на id
   * \brief Покупка и включение в конвоя нового военно-транспортного корабля
   * \param[in] type - тип корабля
   * \param[in] name - имя корабля
   * \param[in] wp1 - название первого оружия
     * \param[in] wp2 - название второго оружия
     * \param[in] wp3 - название третьего оружия
     * \param[in] wp4 - название четвертого оружия
     * \param[in] weight_ - загруженный на данный корабль вес
   * \return id включенного корабля
   * \throw range_error если мы превысили лимит кол-ва кораблей
     * \throw invalid_argument если уже существует корабль с данным id или мы загрузили слишком большой груз на этот корабль
     * \throw overflow_error если мы потратили слишком много денег и превысили лимит
   */
    unsigned long buy_convoy_battle_transport(std::string const &name, WeaponName wp1, WeaponName wp2, WeaponName wp3, WeaponName wp4, int weight_);
    /*!
     * @}
     */

    /*!
     * \defgroup erase Продажа/удаление кораблей
     * \brief Данный модуль предназначен для удаления и продажи кораблей конвоя и пиратов, в частности, при их уничтожении во время боя
     * @{
     */

    /*!
     * Также кроме удаления корабля из таблицы конвоя, учитывается экономическая и логистическая часть, т.е.
     * увеличивается доступный банк денег и необходимый вес для доставки
   * \brief Продажа корабля конвоя
   * \param[in] id - id корабля
   * \return none
     * \throw invalid_argument если не нашли корабль с данным id
   */
    void sell_convoy(unsigned long const &id);

    /*!
   * \brief Уничтожение корабля пиратов
   * \param[in] id - id корабля
   * \return none
     * \throw invalid_argument если не нашли корабль с данным id
   */
    void erase_pirate(unsigned long const &id) const;

    /*!
     * При вызове данного метода, увеличивается число потерянного грузка, т.к. этот метод нужен именно для удаления во время боя
   * \brief Уничтожение корабля конвоя
   * \param[in] id - id корабля
   * \return none
     * \throw invalid_argument если не нашли корабль с данным id
   */
    void erase_convoy(unsigned long const &id);
    /*!
    * @}
    */

    /*!
     * \defgroup count Подсчет кораблей
     * \brief Данный модуль предназначен для подсчета кол-ва кораблей пиратов, конвоя и их типов
     * @{
     */

    /*!
   * \brief Количество кораблей пиратов
   * \param[in] none
   * \return количество кораблей пиратов
   */
    unsigned long count_pirates() const noexcept;

    /*!
   * \brief Количество кораблей конвоя
   * \param[in] none
   * \return количество кораблей конвоя
   */
    unsigned long count_convoy() const noexcept;

    /*!
   * \brief Количество транспортных кораблей конвоя
   * \param[in] none
   * \return количество кораблей конвоя
   */
    int number_convoy_transport() noexcept;

    /*!
   * \brief Количество военного транспорта конвоя
   * \param[in] none
   * \return количество кораблей конвоя
   */
    int number_convoy_battle_transport() noexcept;
    /*!
    * @}
    */

    /*!
    * \defgroup weapon Покупка и продажа вооружения
    * \brief Данный модуль предназначен для покупки и продажи вооружения
    * @{
    */

    /*!
     * В этом методе также учитывается экономическая составляющая, то есть цена корабля будет меняться
   * \brief Покупка оружия на данный корабль, если установка не была произведена, то на этом месте останется старое орудие
   * \param[in] id - id корабля
     * \param[in] type_ - тип оружия которое мы хотим установить
     * \param[in] number - место, на которе оно будет установлено
     * \throw overflow_error - если превысили лимит денег
     * \throw out_of_range - указали number  как > 4 или < 1
     * \throw invalid_argument если не нашли корабль с данным id
   * \return none
   */
    void buy_weapon(unsigned long const &id, WeaponName type_, int number); // покупка вооружения

    /*!
     * В этом методе также учитывается экономическая составляющая, то есть цена корабля будет уменьшатся, а в удаленном месте
     * будет неопределенный тип вооружения
   * \brief Продажа оружия в данном месте корабля
   * \param[in] id - id корабля
     * \param[in] number - место, на которе оно будет установлено
     * \throw out_of_range - указали number  как > 4 или < 1
     * \throw invalid_argument если не нашли корабль с данным id
   * \return none
   */
    void sell_weapon(unsigned long const &id, int number); // продажа вооружения
    /*!
   * @}
   */

    /*!
    * \defgroup weight Загрузка и разгрузка кораблей
    * \brief Данный модуль предназначен для покупки и продажи вооружения
    * @{
    */

    /*!
   * \brief Загрузка корабля определенным грузом
   * \param[in] id - id корабля
     * \param[in] weight_ - количество груза
     * \throw invalid_argument если не нашли корабль с данным id, груз слишком большой или корабль по данному id - боевой
   * \return none
   */
    void upload_weight(unsigned long const &id, int weight_); // загрузка корабля

    /*!
   * \brief Разгрузка корабля определенным грузом
   * \param[in] id - id корабля
     * \param[in] weight_ - количество груза
     * \throw invalid_argument если не нашли корабль с данным id, груз отрицательный или корабль по данному id - боевой
   * \return none
   */
    void unload_weight(unsigned long const &id, int weight_); // разгрузка корабля

    /*!
     * При распределении учитывается отношение скорости корабля к его весу, чтобы добиться максимально возможной скорости
     * конвоя\n
     * Формула распределения скорости:\n
     * \f$ velocity = 1 - \frac{m}{m_m} \f$\n
     * Где \f$m\f$ - вес груза, \f$m_m\f$ - максимально возможно переносимый груз\n
     * Также при распределении учитывается отношение максимально перевозимого груза у двух разных типов - транспорта и военного транспорта\n
     * \n\f$ f = \frac{m_t}{m_b} + 1\f$\n
     * Где \f$m_t\f$ - максимальный вес для транспортного корабля, а \f$m_b\f$ - для военного транспорта\n
     * \n Среднее распределение:\n
     * \n\f$ k = \frac{m}{f * n} * \frac{n_b}{n_t}\f$\n
     * Где \f$m\f$ - вес, необходимы для распределения, \f$n\f$ - общее число кораблей, \f$n_b\f$ - число военного транспорта, \f$n_t\f$ - число транспорта\n
     * \n если количество кораблей конвоя равна 0, то в \f$n_t\f$ = 1\n
     * тогда загрузка веса на транспортный корабль равна:\n
     * \n\f$ x = \frac{m - k * n_b}{n_t} - m_c\f$\n
     * где \f$m_c\f$ - текущий вес на корабле
     * \n Для военного транспорта:\n
     * \n \f$ x = k - m_c \f$\n
   * \brief Автоматическая загрузка всех кораблей конвоя равномерно
   * \param[in] none
     * \throw invalid_argument если недостаточно кораблей для загрузки всего груза
   * \return none
   */
    void upload_automatically(int weight_); // автоматическая загрузка
    /*!
   * @}
   */

    void set_dop(int max_money_, int max_weight_) noexcept{
        money = max_money_;
        max_weight = max_weight_;
    }

    unsigned long get_pirate_id(std::string const &name_ship) const;
    unsigned long get_convoy_id(std::string const &name_ship) const;
    double get_convoy_speed() const noexcept;
    Coord get_pirate_base() const noexcept{
        return base_pirate;
    }
    int get_weight_delivered() const noexcept{
        return weight_delivered;
    }
    void convoy_finish(unsigned long const &id_);
    Coord get_convoy_finish() const noexcept{
        return base[1];
    }
    std::vector<std::pair<unsigned long, int>> *find_to_shoot(unsigned long const &id) const noexcept;
    void shoot(unsigned long const &id_from, unsigned long const &id_to) noexcept;
    void shoot_pirate(unsigned long const &id_from, unsigned long const &id_to) noexcept;
private:
    Table *table_convoy; // таблица конвоя
    Table *table_pirate; // таблица пиратов
    int money; // выделенные деньги
    int spent_money; // потраченные деньги
    int weight; // общий вес груза
    int max_weight; // вес, который нужно довести
    int weight_delivered; // доставленный груз
    int weight_lost; // потерянный груз
    std::array<Coord, 2> base; // базы конвоя
    Coord base_pirate; // базы пиратов

    void set_pirates() const;
};

#endif //LAB4_MISSION_H
