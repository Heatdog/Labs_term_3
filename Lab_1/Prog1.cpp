//
// Created by User on 04.09.2021.
//

#include "Prog1.h"

namespace Prog1{

    void start(Matrix& matrix){// функция для старта программы
        std::cout << "How many lines do you want?" << std::endl;// вводим кол-во строк
        std::string err;
        do{//проверка на правильность ввода кол-ва столбцов и строк
            std::cout << err << std::endl;
            if (!get_n(matrix.rows)){ // проверка на ввод данных
                return;
            }
            err = "You`re wrong! Try again";
        } while (matrix.rows <= 0);
        std::cout << "How many columns do you want?" << std::endl; // столбцов
        err = "";
        do{
            std::cout << err << std::endl;
            if (!get_n(matrix.columns)){
                return;
            }
            err = "You`re wrong! Try again";
        } while (matrix.columns <= 0);
        try {
            matrix.line = new Line<Data> [matrix.rows]; // выделяем память под строки
        }catch (std::bad_alloc const &a) { // проверка на выделение памяти
            std::cout << "Can`t allocate memory for rows " << a.what() << std::endl;
            return;
        }
        input(matrix);
    }

    void input(Matrix& matrix){ // ввод чисел в матрицу
        int n = 0;
        for (int i = 0; i < matrix.rows; ++i){
            std::cout << "Line " << i+1 << std::endl;
            for (int j = 0; j < matrix.columns; ++j){
                if(!get_n(n)){ // вводим число
                    return;
                }
                if (n != 0){ // если оно не равно нулю, то вставляем в наш список
                    Data ptr(n, j);
                    matrix.line[i].push_back(ptr);
                }
            }
        }
    }

    void print(Matrix const &matrix){ //вывод матрицы
        for (int i = 0; i < matrix.rows; ++i){
            std::cout << "||   ";
            Node<Data> *ptr = matrix.line[i].get_head(); // сразу смотрим на начало списка
            for (int j = 0; j < matrix.columns; ++j){
                if (ptr != nullptr && ptr->data.number == j){ // если номер столбца совпал с прикрепленным номером числа
                    std::cout << ptr->data.data << "  "; // выводим
                    ptr = ptr->next;
                } else{
                    std::cout << 0 << "  "; // иначе просто выводим 0
                }
            }
            std::cout << " ||" << std::endl;
        }
    }

    void print_not_rectangular(Matrix const &matrix){
        for (int i = 0; i < matrix.rows; ++i){
            std::cout << "||  ";
            Node<Data> *ptr = matrix.line[i].get_head();
            ptr == nullptr ? print_null(matrix.line[i]) : print_not_null(matrix.line[i]);
            std::cout << "  ||" << std::endl;
        }
    }

    void print_null(Line<Data> const &line){
        for (int i = 0; i < line.get_number(); ++i){
            std::cout << " 0 ";
        }
    }

    void print_not_null(Line<Data> const &line){
        for (Node<Data> *ptr = line.get_head(); ptr != nullptr; ptr = ptr->next){
            std::cout << " " << ptr->data.data << " ";
        }
    }

    void erase(Matrix &matrix){ // удаление матрицы
        delete [] matrix.line;
        matrix.line = nullptr;
    }


    Matrix additional_task(Matrix const &matrix){ // доп задание
        Matrix new_matrix = {0, 0, nullptr};
        try{
            new_matrix.line = new Line<Data> [matrix.rows]; // выделение памяти для списков
        }catch (std::bad_alloc const &a){
            std::cout << "Can`t allocate memory " << a.what() << std::endl;
            return new_matrix;
        }
        new_matrix.columns = matrix.columns; // заполняем тем же кол-вом строк и столбцов
        new_matrix.rows = matrix.rows;
        additional_add(new_matrix, matrix);
        return new_matrix;
    }


    void additional_add(Matrix &new_matrix, Matrix const &matrix){ // добавление чисел для доп задания
        for (int i = 0; i < matrix.rows; ++i){
            Node<Data> *ptr_x = matrix.line[i].get_tail();
            int number = matrix.line[i].get_number();
            if (ptr_x == nullptr){ // все элементы это 0
                new_matrix.line[i].set_number(matrix.columns);
            } else { // есть хотя бы 1 ненулевой элемент
                Data tail = ptr_x->data; // смотрим на конец списка
                if (tail.number + 1 != matrix.columns) { // если последний элемент нулевой
                    // если последний элемент 0, то в новой строке будут только нули, поэтому просто указываем кол-во нулевых элементов
                    new_matrix.line[i].set_number(matrix.columns - number);
                } else {
                    additional_add_not_null(new_matrix.line[i], matrix.line[i]);
                }
            }
        }
    }

    void additional_add_not_null(Line<Data> &new_line, Line<Data> const &line){
        Data tail = line.get_tail()->data;
        int n = tail.data, j = 0;
        for (Node<Data> *ptr = line.get_head(); ptr != nullptr; ptr = ptr->next) { // просматриваем весь список
            Data x(ptr->data.data, j);
            if (comparison(x.data, n)) {
                new_line.push_back(x); // заполняем список значениями с первого списка, при этом сохраняем новые ключи
                j++;
            }
        }
    }


    bool comparison(int a, int b){ // функция сравнения чисел
        int sum1 = 0, sum2 = 0;
        do{
            sum2 += b % 10;
            b = b / 10;
        } while (b % 10 != 0);
        do{
            sum1 += a % 10;
            a = a / 10;
        } while (a % 10 != 0);
        return sum1 == sum2;
    }
}