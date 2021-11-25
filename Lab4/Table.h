//
// Created by User on 06.11.2021.
//

#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

/*!
 * \file
 * \brief Заголовочный файл с описанием класса таблица
 */


#include "Ship.h"
#include <unordered_map>
#include "UnordedNode.h"

/*!
 * \brief Класс координат, нужен для передвижения кораблей
 */

struct Coord{
    int x; ///< x-координата
    int y; ///< y-координата
};

/*!
 * \brief Класс элемента таблицы, содержит информацию о корабле, его положении и id в таблице
 */

struct Element{
public:
    explicit Element(std::shared_ptr<Ship> ship_) noexcept;
    std::shared_ptr<Ship> ship;
    Coord coord{};
    unsigned long get_id() const noexcept{return id;}
private:
    unsigned long id; ///< id корабля
    static unsigned long current_id; ///< текущее id для создания нового
};

/*!
 * \brief Класс таблицы, является оберткой на unordered_map
 */

class Table{
private:
    Lab4::unordered_map<unsigned long, Element> table;
public:
    explicit Table() = default;

    /*!
   * \brief Включение в таблицу
   * \param[in] ship - умный указатель нуа нужный корабль
   * \return id включенного корабля
   * \throw invalid_argument если уже существует корабль с данным id
   */
    unsigned long insert(std::shared_ptr<Ship> ship);

    /*!
   * \brief Удаление из таблицы
   * \param[in] id - id на удаляемый элемент
   * \return none
   * \throw invalid_argument если не нашли корабль с данным id
   */
    void erase(unsigned long const &id);

    /*!
   * \brief Поиск в таблице
   * \param[in] id - id на интересующий нас элемент
   * \return shared_ptr на найденный корабль
   * \throw invalid_argument если не нашли корабль с данным id
   */
    std::shared_ptr<Ship> find(unsigned long const &id) const;

    /*!
   * \brief Подсчет кораблей транспорта
   * \param[in] none
   * \return количество кораблей транспорта
   */
    int count_transport() const noexcept;

    /*!
   * \brief Подсчет военных кораблей
   * \param[in] none
   * \return количество военных кораблей
   */
    int count_battle_transport() const noexcept;

    /*!
   * \brief Подсчет всех кораблей
   * \param[in] none
   * \return количество кораблей всех типов
   */
    unsigned long count() const noexcept;

    /*!
   * \brief Возврат копии таблицы
   * \param[in] none
   * \return unordered_map таблица
   */
    auto get_table() const noexcept {return table;}
};

#endif //LAB4_TABLE_H
