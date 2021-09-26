//
// Created by User on 24.09.2021.
//

#include "Prog3.h"

namespace Prog3{

    int const Number::len = 19;

    Number::Number() {
        input_zero(data, 0, len);
        data[len] = '0';
    }


    Number::Number(long a) {
        try {
            to_bit(a, data, len);
        }catch (std::exception const &a){ // обработка ошибки на слишком большое число
            std::cout << a.what() << std::endl;
        }
    }

    Number::Number(std::string const &a) {
        try {
            long ptr = std::stol(a); // преобразуем в long (проверка на получения числа)
            try {
                to_bit(ptr, data, len);
            }catch (std::exception const &a){ // обработка ошибки на слишком большое число
                std::cout << a.what() << std::endl;
            }
        }catch (std::invalid_argument const &k){
            std::cout << k.what() << std::endl;
            std::cout << "Can`t find a number!" << std::endl;
        }
    }

    void Number::output() const {
        std::cout << data[len] << "`";
        for (int i = len-1; i >= 0; i--) {
            std::cout << data[i];
        }
        std::cout << std::endl;
    }


    void to_bit(long &a, char* data, int const &len){
        char sign;
        a >= 0 ? sign = '0' : sign = '1';
        int i = 0; // записываем в обратном порядке;
        do{
            if (i == len){ // оставляем 1 элемент для записи знака числа
                input_zero(data, 0, len); // заполняем число нулями
                data[len] = '0';
                throw std::out_of_range("This number too big!");
            }
            a % 2 == 0 ? data[i] = '0' : data[i] = '1'; // выбираем, что нам следует записать
            a = a / 2;
            i++;
        } while (a != 0);
        data[len] = sign;
    }

    void input_zero(char a[], int start, int end){
        for (int i = start; i < end; i++){
            a[i] = '0';
        }
    }

    Number Number::dop_code() const{
        Number rev;
        this->sign() == '0' ? copy(data, rev.data, len) : cope_rev(data, rev.data, len);
        return rev;
    }

    char Number::sign() const{
        return data[len];
    }

    void copy(char const a[], char b[], int const &finish){ // обычное копирование чисел (исключение не может быть вызвано, т.к.длины равны)
        for (int i = 0; i <= finish; i++){ // тем более исключение вызвалось на этапе создания экземпляра
            b[i] = a[i];
        }
    }

    void cope_rev(char const a[], char b[], int const &len){ // заполнение для дополнительного кода
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
        b[len] = a[len];
    }


    Number sum(Number &a, Number &b){
        Number result;
        Number a_dop, b_dop;
        a_dop = a.dop_code(), b_dop = b.dop_code(); // новые числа для дополнительного кода
        try {
            bit_sum(a_dop.data, b_dop.data, result.data, Number::len); // суммируем биты + смотрим на переполнение
        } catch (std::exception const &err){
            std::cout << err.what() << std::endl;
        }
        if (result.sign() == '1'){ // Если число отрицательное, то переводим в прямой код, т.к. мы храним числа в прямом коде
            cope_rev(result.data, result.data, Number::len);
        }
        return result;
    }

    void bit_sum(char const a[], char const b[], char s[], int const &len){
        bool flag = false; // флаг для единицы
        for (int i = 0; i <= len; i++){ // суммируем без битового знаком
            if (a[i] == '0' && b[i] == '0') {
                flag ? s[i] = '1' : s[i] = '0';
                flag = false;
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
        if ((a[len] == '0' && b[len] == '0' && s[len] == '1') || (a[len] == '1' && b[len] == '1' && s[len] == '0')){
            input_zero(s, 0, len); // заполняем число нулями
            s[len] = '0';
            throw std::out_of_range ("Переполнение разрядной сетки");
        }
    }


    Number& Number::operator=(Number const &a){ // нужен чтобы можно было переприсваивать результат суммы
        if (this != &a){ // проверяем, не является ли это тем же самым
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

    void Number::get_data(char s[], int l) const {
        if (l < len){
            throw std::out_of_range("Массив слишком маленький!");
        }
        for (int i = 0; i <= len; i++){
            s[i] = data[i];
        }
    }

    /*
    Number& Number::operator++(){
       Number a("1"); // создаем число 1
       *this = sum(*this, a); // суммируем (можно обойтись без вспомогательной, но нужен оператор присваивания)
       return *this;
   }
     */


}

