//
// Created by User on 24.09.2021.
//

#include "Prog3.h"

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

    void Number::output() const {
        if (len != 0) {
            std::cout << data[len] << "`";
            for (int i = len-1; i >= 0; i--) {
                std::cout << data[i];
            }
        }
        std::cout << std::endl;
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

    Number Number::dop_code() const{
        Number rev;
        rev.len = this->len;
        this->sign() == '0' ? copy(this->data, rev.data, this->len) : cope_rev(this->data, rev.data, this->len);
        return rev;
    }

    char Number::sign() const{
        return data[len];
    }

    void copy(char const a[], char b[], int finish){ // обычное копирование чисел (исключение не может быть вызвано, т.к.длины равны)
        for (int i = 0; i <= finish; i++){ // тем более исключение вызвалось на этапе создания экземпляра
            b[i] = a[i];
        }
    }

    void cope_rev(char const a[], char b[], int len){ // заполнение для дополнительного кода
        bool flag = true; // запоминаем единицу, которую хотим добавить, чтобы 2 раза не проходить массив
        for (int i = 0; i < len; i++){
            if (flag){ // добавляем единицу
                if (a[i] == '0'){
                    b[i] = '0';
                } else{
                    b[i] = '1';
                    flag = false;
                }
            } else{ // ничего не добавляем
                if (a[i] == '0') {
                    b[i] = '1';
                } else{
                    b[i] = '0';
                }
            }
        }
        b[len] = a[len]; // знаковое число постоянно
    }


    Number sum(Number &a, Number &b){
        Number result;
        bool comp;
        Number a_dop, b_dop;
        a_dop = a.dop_code(), b_dop = b.dop_code(); // новые числа для дополнительного кода
        int len_max, len_min;
        if (a_dop.len > b_dop.len){
            len_max = a_dop.len;
            len_min = b_dop.len;
            comp = true; // первое число больше 2
        } else {
            len_max = b_dop.len;
            len_min = a_dop.len;
            comp = false; // первое число меньше второго
        }
        comp = bit_sum(a_dop.data, b_dop.data, result.data, len_max, len_min, comp); // суммируем биты + смотрим на переполнение
        comp ? result.len = len_max + 1: result.len = len_max; // если переполнение, то увеличиваем разряд
        if ((a.sign() == '0' && b.sign() == '0') || (a.sign() == '1' && b.sign() == '1')){ // ставим знак
            comp ? result.data[result.len] = '1' : result.data[result.len] = '0'; // если опускался знак - отрицательный
        } else{ // знаки разные
            if(compar(result.data, result.dop_code().data, result.len)){
                result.data[result.len] = '0'; // Прямой и доп. код одинаковы
            } else{
                result.data[result.len] = '1';
            }
        }
        if (result.sign() == '1'){ // Если число отрицательное, то переводим в прямой код, т.к. мы храним числа в прямом коде
            cope_rev(result.data, result.data, result.len);
        }
        return result;
    }

    bool bit_sum(char const a[], char const b[], char s[], int len_max, int len_min, bool comp){
        bool flag = false; // флаг для единицы
        for (int i = 0; i < len_min; i++){ // суммируем без битового знака
            if (a[i] == '0' && b[i] == '0') {
                flag ? s[i] = '1' : s[i] = '0'; // никогда не изменяем флаг
            } else if (a[i] == '1' && b[i] == '1') {
                flag ? s[i] = '1' : s[i] = '0'; // всегда изменяем флаг
                flag = true;
            } else { // в зависимости от случая
                if (flag){
                    s[i] = '0';
                    flag = true;
                } else{
                    s[i] = '1';
                }
            }
        }
        comp ? flag = copy_sum(a, s, len_min, len_max, flag) : flag = copy_sum(b, s, len_min, len_max, flag); // остаток заполнения
        return flag;
    }

    bool copy_sum(char const a[], char s[], int start, int finish, bool flag){ // копирование с учетом флага
        for (int i = start; i < finish; i++){
            if (flag){
                if (a[i] == '1'){
                    s[i] = '0';
                } else{
                    s[i] = '1';
                    flag = false;
                }
            } else{
                s[i] = a[i];
            }
        }
        return flag;
    }


    Number& Number::operator=(Number const &a){ // нужен чтобы можно было переприсваивать результат суммы
        if (this != &a){ // проверяем, не является ли это тем же самым
            len = a.len;
            copy(a.data, data, len);
        }
        return *this;
    }

    Number& Number::prefix() {
        Number a("1"); // создаем число 1
        *this = sum(*this, a); // суммируем
        return *this;
    }

    Number Number::postfix_dec() {
        Number x = *this;
        Number a("-1");
        *this = sum(*this, a);
        return x;
    }

    /*Number& Number::operator++(){
        Number a("1"); // создаем число 1
        *this = sum(*this, a); // суммируем (можно обойтись без вспомогательной, но нужен оператор присваивания)
        return *this;
    }*/

    bool compar(char const a[], char const b[], int len){
        for (int i = 0; i <= len; i++){
            if (a[i] != b[i]){
                return false;
            }
        }
        return true;
    }
}

