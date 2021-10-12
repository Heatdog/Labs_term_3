//
// Created by User on 12.10.2021.
//

#ifndef LAB3DYNEMIC_PROG3_H
#define LAB3DYNEMIC_PROG3_H

#include <iostream>

namespace Dynamic{

    class Number {
    public:
        Number() noexcept;
        char sign() const noexcept; // знак
        Number(Number const &a) noexcept; // конструктор копирования
        ~Number() noexcept;
        Number(long a);
        Number dop_code() const noexcept; // дополнительный код (передавать по ссылке куда мы хотим записать)
        Number(std::string const &a);
        std::string &output(std::string &str) const; // вывод в переменную string
        Number(Number && a) noexcept; // перемещающийся конструктор

        // перегрузка
        Number& operator++() noexcept;
        Number operator--(int) noexcept;
        Number& operator=(Number const &a) noexcept; // оператор присваивания
        Number& operator+=(Number const &a) noexcept;
        Number& operator=(Number && a) noexcept; // перемещающийся оператор присваивания

        friend std::ostream &operator<<(std::ostream &os, Number const &num) noexcept;
    private:
        int len;
        char *data;
    };


    std::istream &input(std::istream &is, Number &num) noexcept;
    std::ostream &output(std::ostream &os, Number const &num) noexcept;
    void one_bit_sum(char const &a, char const &b, char &s, bool &flag) noexcept;
    char *dop_add(char const *a, char const *b, char *s, int const &len, int &i, bool &flag) noexcept;
    char *to_bit(long &a, char* data, int &len) noexcept; // представление в двоичном виде
    char *cope_rev(char const *a, char *b, int len) noexcept; // копирование в дополнительном коде
    char *bit_sum(char const *a, char const *b, char *s, int len_a, int len_b, int &len) noexcept; // битовая сумма
    char *copy(char const *a, char *b, int len) noexcept;

    // перегрузка
    std::istream &operator>>(std::istream &is, Number &num) noexcept;
    Number operator+(Number num1, Number const &num2) noexcept;
}

#endif //LAB3DYNEMIC_PROG3_H
