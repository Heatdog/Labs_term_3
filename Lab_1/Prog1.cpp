//
// Created by User on 04.09.2021.
//

#include "Prog1.h"

namespace Prog1{

    void start(Matrix& matrix){// функция для старта программы
        std::cout << "How many lines do you want?" << std::endl;// вводим кол-во строк
        get_n(matrix.rows);
        std::cout << "How many columns do you want?" << std::endl; // столбцов
        get_n(matrix.columns);
        matrix.line = new Line<Data> [matrix.rows]; // выделяем память под строки
        input(matrix);
    }

    void input(Matrix& matrix){ // ввод чисел в матрицу
        int n = 0;
        for (int i = 0; i < matrix.rows; ++i){
            std::cout << "Line " << i+1 << std::endl;
            for (int j = 0; j < matrix.columns; ++j){
                get_n(n); // вводим число
                if (n != 0){ // если оно не равно нулю, то вставляем в наш список
                    Data ptr(n, j);
                    matrix.line[i].push_back(ptr);
                }
            }
        }
    }

    void print(Matrix const &matrix){ //вывод матрицы
        for (int i = 0; i < matrix.rows; ++i){
            Node<Data> *ptr = matrix.line[i].get_head(); // сразу смотрим на начало списка
            for (int j = 0; j < matrix.columns; ++j){
                if (ptr->data.number == j){ // если номер столбца совпал с прикрепленным номером числа
                    std::cout << ptr->data.data << " "; // выводим
                    ptr = ptr->next;
                } else{
                    std::cout << 0 << " "; // иначе просто выводим 0
                }
            }
            std::cout << std::endl;
        }
    }

    void erase(Matrix &matrix){ // удаление матрицы
        delete [] matrix.line;
        matrix.line = nullptr;
    }
/*

    Matrix additional_task(Matrix const &matrix){ // доп задание
        Matrix new_matrix;
        new_matrix.k = matrix.k;
        new_matrix.line = new Line [matrix.k];
        additional_add(new_matrix, matrix);
        return new_matrix;
    }


    void additional_add(Matrix &new_matrix, Matrix const &matrix){ // добавление чисел для доп задания
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

    bool comparison(int a, int b){ // функция сравнения чисел
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

    int *new_line(int const old_line[], int n){ // перезапись строки
        int *line = new int [n];
        for (int i = 0; i < n; ++i){
            line[i] = old_line[i];
        }
        delete [] old_line;
        return line;
    }
    */

}

