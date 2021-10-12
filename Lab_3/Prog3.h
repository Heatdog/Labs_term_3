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
        char sign() const noexcept; // знак
        void output(std::ostream &os) const noexcept; // вывод в поток
        Number(Number const &a) noexcept; // конструктор копирования (move семантика)

        // выбрасывают исключения
        Number(long a);
        Number dop_code() const; // дополнительный код (передавать по ссылке куда мы хотим записать)
        Number(std::string const &a);
        Number& prefix(); // и постфикс
        Number postfix_dec();
        std::string &output(std::string &str) const; // вывод в переменную string

        // перегрузка
        Number& operator++();
        Number operator--(int);
        Number& operator=(Number const &a) noexcept; // оператор присваивания
        Number& operator+=(Number const &a);


        friend Number sum(Number const &a, Number const &b); // сумма 2 чисел
    private:
        static int const max = 10; // последний элемент (для знака)
        int len;
        char data[max]; // храню число в обратном порядке (включая знак, находящейся в конце массива)
    };

    // безопасные
    std::istream &input(std::istream &is, Number &num) noexcept;
    std::ostream &output(std::ostream &os, Number const &num) noexcept;
    void copy(char const a[], char b[], int len, int max) noexcept; // копирование чисел из массива 1 в 2
    void one_bit_sum(char const &a, char const &b, char &s, bool &flag) noexcept;
    void dop_add(char const a[], char const b[], char s[], int const &len, int &i, int max, bool &flag) noexcept;

    // с исключением
    void to_bit(long &a, char* data, int &len, int max); // представление в двоичном виде
    void cope_rev(char const a[], char b[], int len, int max); // копирование в дополнительном коде
    void bit_sum(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max); // битовая сумма

    // перегрузка
    std::istream &operator>>(std::istream &is, Number &num) noexcept;
    std::ostream &operator<<(std::ostream &os, Number const &num) noexcept;
    Number operator+(Number num1, Number const &num2);
}


#endif //LAB_3_PROG3_H
