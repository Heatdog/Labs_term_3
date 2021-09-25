//
// Created by User on 24.09.2021.
//

#ifndef LAB_3_PROG3_H
#define LAB_3_PROG3_H

#include <iostream>

namespace Prog3 {

    class Number {
    public:
        Number():len(0){};
        explicit Number(long a);
        explicit Number(std::string const &a);
        void output() const; // вывод
        Number dop_code() const; // дополнительный код
        char sign() const; // знак
        Number& prefix();
        Number postfix_dec();
        Number& operator=(Number const &a); // оператор присваивания (в основном для суммы)

        friend Number sum(Number &a, Number &b); // сумма 2 чисел
    private:
        int const max = 20; // максимальная длина
        int len; // длина массива битов
        char data[20]; // храню число в обратном порядке (включая знак, находящейся по индексу len)
    };

    void to_bit(long &a, char* data, int &len, int const &max); // представление в двоичном виде
    void copy(char const a[], char b[], int finish); // копирование чисел из массива 1 в 2
    void cope_rev(char const a[], char b[], int len); // копирование в дополнительном коде
    bool bit_sum(char const a[], char const b[], char s[], int len_max, int len_min, bool comp); // битовая сумма
    bool copy_sum(char const a[], char s[], int start, int finish, bool flag); // копирование с учетом флага
    bool compar(char const a[], char const b[], int len); // сравнение 2 чисел
}


#endif //LAB_3_PROG3_H
