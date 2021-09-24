//
// Created by User on 24.09.2021.
//

#include "Prog3.h"
#include <cstdlib>

namespace Prog3{
    Number::Number(long a) {
        try {
            to_bit(a, data, len, max);
        }catch (std::exception const &a){ // обработка ошибки на слишком большое число
            std::cout << a.what() << std::endl;
        }
    }

    Number::Number(std::string const &a) {
        try {
            long ptr = std::stol(a); // преобразуем в long (проверка на получения числа)
            try { // насколько это уместно для аварийного завершения работы? Ну, то есть чтобы to_bit вообще не выполнялся
                to_bit(ptr, data, len, max);
            }catch (std::exception const &a){ // обработка ошибки на слишком большое число
                std::cout << a.what() << std::endl;
            }
        }catch (std::invalid_argument const &k){
            std::cout << k.what() << std::endl;
            std::cout << "Can`t find a number!" << std::endl;
            len = 0; // зануляем длину, т.к. ничего не смогли считать
        }
    }

    void Number::output() {
        if (len != 0) {
            for (int i = len; i >= 0; i--) {
                std::cout << data[i];
            }
        }
    }


    void to_bit(long &a, char* data, int &len, int const &max){
        char sign;
        a >= 0 ? sign = '0' : sign = '1';
        int i = 0; // записываем в обратном порядке;
        do{
            if (i-1 == max){ // оставляем 1 элемент для записи знака числа
                len = 0; // зануляем длину
                throw std::out_of_range("This number too big!");
            }
            a % 2 == 0 ? data[i] = '0' : data[i] = '1'; // выбираем, что нам следует записать
            a = a / 2;
            i++;
        } while (a != 0);
        len = i;
        data[len] = sign;
    }
}

