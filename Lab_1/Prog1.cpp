//
// Created by User on 04.09.2021.
//

#include "Prog1.h"

namespace Prog1{
    void start(Matrix& matrix){
        std::cout << "How many lines do you want?" << std::endl;
        get_n(matrix.k);
        input(matrix);
    }

    void input(Matrix& matrix){
        matrix.line = new Line[matrix.k];
        int n;
        for (int i = 0; i < matrix.k; ++i){
            std::cout << "Enter number of columns in line " << i+1 << std::endl;
            get_n(n);
            matrix.line[i].n = n;
            matrix.line[i].data = new int[n];
            for (int j = 0; j < n; ++j){
                get_n(matrix.line[i].data[j]);
            }
        }
    }

    void print(Matrix const &matrix){
        for (int i = 0; i < matrix.k; ++i){
            for (int j = 0; j < matrix.line[i].n; ++j){
                std::cout << matrix.line[i].data[j];
            }
            std::cout << std::endl;
        }
    }

    void erase(Matrix &matrix){
        for (int i = 0; i < matrix.k; ++i){
            delete [] matrix.line[i].data;
        }
        delete [] matrix.line;
        matrix.line = nullptr;
    }

    Matrix additional_task(Matrix const &matrix){
        Matrix new_matrix;
        new_matrix.k = matrix.k;
        new_matrix.line = new Line [matrix.k];
        additional_add(new_matrix, matrix);
        return new_matrix;
    }

    void additional_add(Matrix &new_matrix, Matrix const &matrix){
        int n = 0, j;
        for (int i = 0; i < matrix.k; ++i){
            int k = matrix.line[i].n;
            new_matrix.line[i].data = new int [k];
            for (j = 0; j < k-1; ++j){//записываем все подходящие числа
                if (comparison(matrix.line[i].data[j], matrix.line[i].data[k-1])){
                    new_matrix.line[i].data[n] = matrix.line[i].data[j];
                    n++;
                }
            }
            n++;//записываем последний элемент
            new_matrix.line[i].data[n-1] = matrix.line[i].data[k-1];
            new_matrix.line[i].n = n;
            if (k / 2 >= n && k >= 5){ // если кол-во элементов сильно меньше по сравнению с длиной строки
                new_matrix.line[i].data = new_line(new_matrix.line[i].data, n);
            }
        }
    }

    bool comparison(int a, int b){
        int sum1 = 0, sum2 = 0;
        do{
            sum2 += b % 10;
            b = b / 10;
        } while (b % 10 != b);
        do{
            sum1 += a % 10;
            a = a / 10;
        } while (a % 10 != a);
        return sum1 == sum2;
    }

    int *new_line(int const old_line[], int n){
        int *line = new int [n];
        for (int i = 0; i < n; ++i){
            line[i] = old_line[i];
        }
        delete [] old_line;
        return line;
    }
}

