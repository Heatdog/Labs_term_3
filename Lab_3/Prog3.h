//
// Created by User on 24.09.2021.
//

#ifndef LAB_3_PROG3_H
#define LAB_3_PROG3_H

#include <iostream>

namespace Prog3 {

    class Number {
    public:
        Number();
        explicit Number(long a);
        explicit Number(std::string const &a);
        void output() const; // вывод
        Number dop_code() const; // дополнительный код
        char sign() const; // знак
        void get_data(char s[], int l) const;
        Number& operator=(Number const &a); // оператор присваивания
        Number(Number const &a); // конструктор копирования
        Number& prefix();
        Number postfix_dec();

        friend Number sum(Number &a, Number &b); // сумма 2 чисел
    private:
        static int const len; // последний элемент (для знака)
        char data[10]; // храню число в обратном порядке (включая знак, находящейся в конце массива)
    };

    void to_bit(long &a, char* data, int const &len); // представление в двоичном виде
    void input_zero(char a[], int start, int end);
    void copy(char const a[], char b[], int const &finish); // копирование чисел из массива 1 в 2
    void cope_rev(char const a[], char b[], int const &len); // копирование в дополнительном коде
    void bit_sum(char const a[], char const b[], char s[], int  const &len); // битовая сумма
}


#endif //LAB_3_PROG3_H
