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

    bool start(Matrix& matrix);
    bool input(Matrix& matrix);
    Matrix additional_task(Matrix const &matrix);
    void print(Matrix const &matrix);
    void print_not_rectangular(Matrix const &matrix);
    void print_null(Line<Data> const &line);
    void print_not_null(Line<Data> const &line);
    void erase(Matrix &matrix);
    void additional_add(Matrix &new_matrix, Matrix const &matrix);
    void additional_add_not_null(Line<Data> &new_matrix, Line<Data> const &matrix);
    int summ(int a);

}

#endif //LAB_1_PROG1_H
