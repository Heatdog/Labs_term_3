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
        char sign() const noexcept; // 8) выполнение операции определения знака числа.
        ~Number() noexcept; // деструктор
        Number(Number && a) noexcept; // перемещающийся конструктор

        // с исключением
        Number(); // 1) пустой конструктор для инициализации экземпляров и массивов экземпляров класса по умолчанию;
        Number(Number const &a); // конструктор копирования
        Number(long a); // 2) создание экземпляров класса с инициализацией значением целого числа типа long;
        Number dop_code() const; // 5) получение дополнительного кода числа;
        Number(std::string const &a); // 3) создание экземпляров класса с инициализацией значением числа как строки символов;
        std::string &output(std::string &str) const; // вывод в переменную string

        // перегрузка
        Number& operator++() ; // 7) выполнение операции увеличения числа на единицу до использования числа;
        Number operator++(int); // (доп задание) постфикс
        Number operator--(int) ; //  выполнение операции уменьшения числа после его использования;
        Number& operator--(); // (доп задание) префикс
        Number& operator=(Number const &a); // оператор присваивания
        Number& operator+=(Number const &a); // 6) выполнение операции сложения чисел с разными знаками в дополнительном коде;
        Number& operator=(Number && a) noexcept; // перемещающийся оператор присваивания

        friend std::ostream &operator<<(std::ostream &os, Number const &num) noexcept; // 4) вывод их значений в выходной поток;
    private:
        int len;
        char *data;
    };


    void one_bit_sum(char const &a, char const &b, char &s, bool &flag) noexcept; // суммирование 1 бита
    char *dop_add(char const *a, char const *b, char *s, int const &len, int &i, bool &flag) noexcept;
    char *to_bit(long &a, char* data, int &len); // представление в двоичном виде
    char *cope_rev(char const *a, char *b, int len) noexcept; // копирование в дополнительном коде
    char *bit_sum(char const *a, char const *b, char *s, int len_a, int len_b, int &len) noexcept; // битовая сумма
    char *copy(char const *a, char *b, int len) noexcept; // копирование
    void reduce_bits(char *s, int &len) noexcept; // уменьшение разрядной сетки

    // перегрузка
    std::istream &operator>>(std::istream &is, Number &num) noexcept; // 4) ввод экземпляров класса из входного потока
    Number operator+(Number num1, Number const &num2); // 6) выполнение операции сложения чисел с разными знаками в дополнительном коде;
}

#endif //LAB3DYNEMIC_PROG3_H
