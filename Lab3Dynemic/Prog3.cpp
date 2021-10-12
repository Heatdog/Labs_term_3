//
// Created by User on 12.10.2021.
//

#include "Prog3.h"

namespace Dynamic{
    Number::Number() noexcept : len(0), data(nullptr){}

    Number::Number(long a) {
        to_bit(a, data, len);
    }

    Number::Number(std::string const &a) {
        long ptr = std::stol(a);
        to_bit(ptr, data, len);
    }

    Number::~Number(){
        delete [] data;
        len = 0;
    }

    void to_bit(long &a, char* data, int &len){
        int max = 20;
        data = new char [max];
        a >= 0 ? data[0] = '0' : data[0] = '1';
        int i = 1; // записываем в обратном порядке
        do{
            if (i == max){
                max += 20;
                char *data_new = new char [max];
                copy(data, data_new, 0, max-20);
                delete [] data;
                data = data_new;
            }
            a % 2 == 0 ? data[i] = '0' : data[i] = '1'; // выбираем, что нам следует записать
            a = a / 2;
            i++;
        } while (a != 0);
        len = i;
    }

    void copy(char const *a, char *b, int start, int finish){
        if (finish < start){
            throw std::logic_error("Неправильно указаны области копирования!");
        }
        for (int i = start; i < finish; i++){
            b[i] = a[i];
        }
    }

    std::string &Number::output(std::string &str) const{
        if (len != 0) {
            str.resize(len + 1); // отмечаем длину строки
            str.at(0) = data[0];
            for (int i = len - 1, j = 1; i >= 0; i--, j++) {
                str.at(j) = data[i];
            }
        }
        return str;
    }


}
