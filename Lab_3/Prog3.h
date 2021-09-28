//
// Created by User on 24.09.2021.
//

#ifndef LAB_3_PROG3_H
#define LAB_3_PROG3_H

#include <iostream>

namespace Prog3 {

    class Number {
    public:
        // безопасные
        Number() noexcept;
        void output() const noexcept; // вывод
        char sign() const noexcept; // знак
        Number& operator=(Number const &a) noexcept; // оператор присваивания
        Number(Number const &a) noexcept; // конструктор копирования

        // выбрасывают исключения
        explicit Number(long a);
        Number dop_code() const; // дополнительный код
        explicit Number(std::string const &a);
        Number& prefix();
        Number postfix_dec();
        void get_data(char s[], int l) const;

        friend Number sum(Number const &a, Number const &b); // сумма 2 чисел
    private:
        static int const len; // последний элемент (для знака)
        char data[10]; // храню число в обратном порядке (включая знак, находящейся в конце массива)
    };

    // безопасные
    void input_zero(char a[], int start, int end) noexcept;
    void copy(char const a[], char b[], int const &finish) noexcept; // копирование чисел из массива 1 в 2
    void one_bit_sum(char const &a, char const &b, char &s, bool &flag) noexcept;

    // с исключением
    void to_bit(long &a, char* data, int const &len); // представление в двоичном виде
    void cope_rev(char const a[], char b[], int const &len); // копирование в дополнительном коде
    void bit_sum(char const a[], char const b[], char s[], int  const &len); // битовая сумма
}


#endif //LAB_3_PROG3_H
