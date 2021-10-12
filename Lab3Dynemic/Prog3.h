//
// Created by User on 12.10.2021.
//

#ifndef LAB3DYNEMIC_PROG3_H
#define LAB3DYNEMIC_PROG3_H

#include <iostream>

namespace Dynamic{

    class Number {
    public:
        // безопасные
        Number() noexcept;
        char sign() const noexcept; // знак
        void output(std::ostream &os) const noexcept; // вывод в поток
        Number(Number const &a) noexcept; // конструктор копирования (move семантика)
        ~Number();

        // выбрасывают исключения
        Number(long a);
        Number dop_code() const; // дополнительный код (передавать по ссылке куда мы хотим записать)
        Number(std::string const &a);
        std::string &output(std::string &str) const; // вывод в переменную string

        // перегрузка
        Number& operator++();
        Number operator--(int);
        Number& operator=(Number const &a) noexcept; // оператор присваивания
        Number& operator+=(Number const &a);


    private:
        int len;
        char *data;
    };

    // безопасные
    std::istream &input(std::istream &is, Number &num) noexcept;
    std::ostream &output(std::ostream &os, Number const &num) noexcept;
    void one_bit_sum(char const &a, char const &b, char &s, bool &flag) noexcept;
    void dop_add(char const a[], char const b[], char s[], int const &len, int &i, int max, bool &flag) noexcept;

    // с исключением
    void to_bit(long &a, char* data, int &len); // представление в двоичном виде
    void cope_rev(char const a[], char b[], int len, int max); // копирование в дополнительном коде
    void bit_sum(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max); // битовая сумма
    void copy(char const *a, char *b, int start, int finish);

    // перегрузка
    std::istream &operator>>(std::istream &is, Number &num) noexcept;
    std::ostream &operator<<(std::ostream &os, Number const &num) noexcept;
    Number operator+(Number num1, Number const &num2);
}

#endif //LAB3DYNEMIC_PROG3_H
