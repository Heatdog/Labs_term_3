//
// Created by User on 04.09.2021.
//

#ifndef LAB_1_PROG1_H
#define LAB_1_PROG1_H

#include <iostream>
#include "Alg.h"

namespace Prog1{
    struct Data{
        explicit Data(int data = 0, int number = 0):data(data), number(number){}
        int data;//значение
        int number;//номер в строке
    };

    struct Matrix{
        int columns; // кол-во столбцов
        int rows; // кол-во строк
        Line<Data> *line;
    };

    template <class T>
    bool get_n(T& n){
        std::cout << "Enter number" << std::endl;
        std::cin >> n;
        return std::cin.good();
    }

    void start(Matrix& matrix);
    void input(Matrix& matrix);
    //Matrix additional_task(Matrix const &matrix);
    void print(Matrix const &matrix);
    void erase(Matrix &matrix);
    //void additional_add(Matrix &new_matrix, Matrix const &matrix);
    //bool comparison(int a, int b);
    //int *new_line(int const old_line[], int n);

}

#endif //LAB_1_PROG1_H
