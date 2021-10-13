//
// Created by User on 24.09.2021.
//

#ifndef LAB_3_PROG3_H
#define LAB_3_PROG3_H

#include <iostream>

namespace Static {

    class Number {
    public:
        // безопасные
        Number() noexcept;
        void output() const noexcept; // вывод в консоль
        char sign() const noexcept; // знак числа
        void output(std::ostream &os) const noexcept; // вывод в поток
        Number(Number const &a) noexcept; // конструктор копирования
        Number(Number && a) noexcept; // перемещающийся конструктор
        static int get_max() noexcept; // возврат максимально возможное кол-во цифр в числе без знака

        // выбрасывают исключения
        Number(long a);
        Number dop_code() const; // дополнительный код
        Number(std::string const &a);
        Number& prefix();
        Number postfix_dec();
        std::string &output(std::string &str) const; // вывод в переменную string

        // перегрузка
        Number& operator++(); // префикс инкремент
        Number operator++(int); // постфиксный инкремент
        Number operator--(int); // постфиксный декремент
        Number& operator--(); // префиксный декремент
        Number& operator=(Number const &a) noexcept; // оператор присваивания
        Number& operator+=(Number const &a);
        Number& operator=(Number && a) noexcept; // перемещающийся оператор присваивания

        friend Number sum(Number const &a, Number const &b); // сумма 2 чисел
    private:
        static int const max = 10; // последний элемент (для знака)
        int len;
        char data[max]; // храню число в обратном порядке (включая знак, находящейся в конце массива)
    };

    // безопасные
    std::istream &input(std::istream &is, Number &num) noexcept; // ввод с потока
    std::ostream &output(std::ostream &os, Number const &num) noexcept; // вывод в поток
    void copy(char const a[], char b[], int len, int max) noexcept; // копирование чисел из массива 1 в 2
    void one_bit_sum(char const &a, char const &b, char &s, bool &flag) noexcept; // сумма одного разряда
    void dop_add(char const a[], char const b[], char s[], int const &len, int &i, int max, bool &flag) noexcept; // суммирование до одного разряда

    // с исключением
    void to_bit(long &a, char* data, int &len, int max); // представление в двоичном виде
    void cope_rev(char const a[], char b[], int len, int max); // копирование в дополнительном коде
    void bit_sum(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max); // битовая сумма

    // перегрузка
    std::istream &operator>>(std::istream &is, Number &num) noexcept;
    std::ostream &operator<<(std::ostream &os, Number const &num) noexcept;
    Number operator+(Number const &num1, Number const &num2);
}


#endif //LAB_3_PROG3_H
