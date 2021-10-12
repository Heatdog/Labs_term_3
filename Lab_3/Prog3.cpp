//
// Created by User on 24.09.2021.
//

#include "Prog3.h"

namespace Static{

    Number::Number() noexcept {
        len = 0;
    }


    Number::Number(long a) {
        to_bit(a, data, len, max);
    }

    Number::Number(std::string const &a) {
        long ptr = std::stol(a); // преобразуем в long (проверка на получения числа) своя функция на сочень большие числа
        to_bit(ptr, data, len, max);
    }

    void Number::output() const noexcept { // передавать поток по ссылке
        if (len != 0) {
            std::cout << data[max - 1] << "`";
            for (int i = len - 1; i >= 0; i--) {
                std::cout << data[i];
            }
            std::cout << std::endl;
        }
    }

    std::string &Number::output(std::string &str) const {
        if (len != 0) {
            str.resize(len + 1); // отмечаем длину строки
            str.at(0) = data[max - 1];
            for (int i = len - 1, j = 1; i >= 0; i--, j++) {
                str.at(j) = data[i];
            }
        }
        return str;
    }

    void Number::output(std::ostream &os) const noexcept{
        if (len != 0){
            os << data[max - 1];
            for (int i = len - 1; i >= 0; i--) {
                os << data[i];
            }
            os << std::endl;
        }
    }


    void to_bit(long &a, char* data, int &len, int max){
        char sign;
        a >= 0 ? sign = '0' : sign = '1';
        int i = 0; // записываем в обратном порядке
        do{
            if (i+1 >= max){ // оставляем 1 элемент для записи знака числа
                throw std::out_of_range("This number too big!");
            }
            a % 2 == 0 ? data[i] = '0' : data[i] = '1'; // выбираем, что нам следует записать
            a = a / 2;
            i++;
        } while (a != 0);
        len = i;
        data[max-1] = sign;
    }

    Number Number::dop_code() const{
        Number rev;
        this->sign() == '0' ? copy(data, rev.data, len, max) : cope_rev(data, rev.data, len, max);
        rev.len = len;
        return rev;
    }

    char Number::sign() const noexcept{
        return data[max-1];
    }

    void copy(char const a[], char b[], int len, int max) noexcept{ // обычное копирование чисел (исключение не может быть вызвано, т.к.длины равны)
        for (int i = 0; i < len; i++){ // тем более исключение вызвалось на этапе создания экземпляра
            b[i] = a[i];
        }
        b[max-1] = a[max-1];
    }

    void cope_rev(char const a[], char b[], int len, int max){ // заполнение для дополнительного кода
        bool flag = true; // запоминаем единицу, которую хотим добавить, чтобы 2 раза не проходить массив
        int k = 0, i; // k нужна для выявления переполнения при переходе из доп кода в прямой
        for (i = 0; i < len; i++){
            if (flag){ // добавляем единицу
                if (a[i] == '0'){
                    b[i] = '0';
                    k++;
                } else{
                    b[i] = '1';
                    flag = false;
                }
            } else{ // ничего не добавляем
                if (a[i] == '0') {
                    b[i] = '1';
                } else{
                    b[i] = '0';
                    k++;
                }
            }
        }
        if (a[max-1] == '1' && i == k){
            throw std::invalid_argument("Доп ->  прямой: случилось переполнение");
        }
        b[max-1] = a[max-1];
    }


    Number sum(Number const &a, Number const &b){
        Number result;
        Number a_dop(a.dop_code()), b_dop(b.dop_code()); // новые числа для дополнительного кода
        bit_sum(a_dop.data, b_dop.data, result.data, a.len, b.len, result.len, Number::max); // суммируем биты + смотрим на переполнение
        if (result.sign() == '1'){ // Если число отрицательное, то переводим в прямой код, т.к. мы храним числа в прямом коде
            cope_rev(result.data, result.data, result.len, Number::max);
        }
        return result;
    }

    void bit_sum(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max){
        bool flag = false; // флаг для единицы
        int len_f, i;
        len_a > len_b ? len_f = len_b : len_f = len_a;
        for (i = 0; i < len_f; i++){ // суммируем без битового знаком и до разряда меньшего числа
            one_bit_sum(a[i], b[i], s[i], flag);
        }
        len_a > len_b ? dop_add(a, b, s, len_a, i, max, flag) : dop_add(b, a, s, len_b, i, max, flag); // расширение до одного разряда
        if ((flag && a[max-1] == '0' && b[max-1] == '0') || (!flag && a[max-1] == '1' && b[max-1] == '1')){ // хотим расширить разрядную сетку
            if (i < max-2) { // можем расширить разрядную сетку для ответа
                if (a[max - 1] == '0') {
                    s[i] = '1';
                    flag = false;
                } else {
                    s[i] = '0';
                    flag = true;
                }
                i++;
            } else{ // иначе ответ выйдет на знаковую часть -> ответ уже не будет правильным
                throw std::out_of_range ("Переполнение разрядной сетки");
            }
        }
        one_bit_sum(a[max-1], b[max-1], s[max-1], flag); // считаем знак числа
        len = i;
    }

    void dop_add(char const a[], char const b[], char s[],int const &len, int &i, int max, bool &flag) noexcept{
        if (b[max-1] == '0'){ // суммируем в зависимости от знака меньшего числа
            for (; i < len; i++){
                one_bit_sum('0', a[i], s[i], flag);
            }
        } else{
            for (; i < len; i++){
                one_bit_sum('1', a[i], s[i], flag);
            }
        }
    }


    Number& Number::operator=(Number const &a) noexcept{ // нужен чтобы можно было переприсваивать результат суммы
        if (this != &a){ // проверяем, не является ли это тем же самым
            copy(a.data, data, a.len, Number::max);
            len = a.len;
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
        Number a(-1);
        *this = sum(*this, a);
        return x;
    }

    Number::Number(Number const &a) noexcept{
        copy(a.data, data, a.len, Number::max);
        len = a.len;
    }

    void one_bit_sum(char const &a, char const &b, char &s, bool &flag) noexcept{
        if (a == '0' && b == '0') {
            flag ? s = '1' : s = '0';
            flag = false;
        } else if (a == '1' && b == '1') {
            flag ? s = '1' : s = '0'; // всегда изменяем флаг
            flag = true;
        } else { // в зависимости от случая
            if (flag){
                s = '0';
                flag = true;
            } else{
                s = '1';
            }
        }
    }

    std::istream &input(std::istream &is, Number &num) noexcept {
        std::string result;
        is >> result;
        if (is.fail()) {
            is.clear();
            is.ignore(32767, '\n');
        } else {
            try {
                num = Number(result);
            } catch (std::invalid_argument const &err1) {
                is.setstate(std::ios::failbit);
            } catch (std::out_of_range const &err2) {
                is.setstate(std::ios::failbit);
            }
        }
        return is;
    }

    std::ostream &output(std::ostream &os, Number const &num) noexcept{
        num.output(os);
        return os;
    }

    std::istream &operator>>(std::istream &is, Number &num) noexcept{
        std::string result;
        is >> result;
        if (is.fail()){
            is.clear();
            is.ignore(32767,'\n');
        } else {
            try {
                num = Number(result);
            } catch (std::invalid_argument const &err1) {
                is.setstate(std::ios::failbit);
            } catch (std::out_of_range const &err2) {
                is.setstate(std::ios::failbit);
            }
        }
        return is;
    }

    std::ostream &operator<<(std::ostream &os, Number const &num) noexcept{
        num.output(os);
        return os;
    }

    Number& Number::operator+=(Number const &a){
        Number a_dop(a.dop_code()), b_dop(this->dop_code());
        bit_sum(a_dop.data, b_dop.data, this->data, a.len, this->len, this->len, Number::max);
        if (this->sign() == '1'){
            cope_rev(this->data, this->data, this->len, Number::max);
        }
        return *this;
    }

    Number operator+(Number num1, Number const &num2){
        return num1+=num2;
    }

    Number Number::operator--(int){
        Number x(*this);
        Number a(-1);
        *this += a;
        return x;
    }

    Number& Number::operator++(){
        Number a("1");
        *this += a;
        return *this;
    }

    Number::Number(Number && a) noexcept{
        copy(a.data, data, a.len, Number::max);
        len = a.len;
        a.len = 0;
    }

    Number& Number::operator=(Number && a) noexcept{
        copy(a.data, data, a.len, Number::max);
        len = a.len;
        a.len = 0;
        return *this;
    }


}

