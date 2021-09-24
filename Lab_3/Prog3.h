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
        void output();


    private:
        int const max = 20; // максимальная длина
        int len; // длина массива битов
        char data[20]; //буду хранить число в обратном порядке (включая знак, находящейся по индексу len)
    };

    void to_bit(long &a, char* data, int &len, int const &max);

}


#endif //LAB_3_PROG3_H
