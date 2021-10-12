//
// Created by User on 12.10.2021.
//

#include "Prog3.h"

namespace Dynamic{
    Number::Number() noexcept : len(0), data(nullptr){}

    Number::Number(long a) {
        data = to_bit(a, data, len);
    }

    Number::Number(std::string const &a) {
        long ptr = std::stol(a);
        data = to_bit(ptr, data, len);
    }

    Number::~Number() noexcept{
        delete [] data;
        len = 0;
    }

    char *to_bit(long &a, char *data, int &len) noexcept{
        int max = 20;
        char *data_new = nullptr;
        try {
            data = new char[max];
        }catch (std::bad_alloc const &err){
            return nullptr;
        }
        a >= 0 ? data[0] = '0' : data[0] = '1';
        int i = 1; // записываем в обратном порядке
        do{
            if (i == max){
                max += 20;
                try {
                    data_new = new char[max];
                }catch (std::bad_alloc const &err){
                    return nullptr;
                }
                data_new = copy(data, data_new, max-20);
                delete [] data;
                data = data_new;
            }
            a % 2 == 0 ? data[i] = '0' : data[i] = '1'; // выбираем, что нам следует записать
            a = a / 2;
            i++;
        } while (a != 0);
        len = i-1;
        return data;
    }

    char *copy(char const *a, char *b, int len) noexcept{
        for (int i = 0; i <= len; i++){
            b[i] = a[i];
        }
        return b;
    }

    std::string &Number::output(std::string &str) const{
        if (len != 0) {
            str.resize(len+1); // отмечаем длину строки
            str.at(0) = data[0];
            for (int i = len, j = 1; i > 0; i--, j++) {
                str.at(j) = data[i];
            }
        }
        return str;
    }

    char Number::sign() const noexcept{
        return data[0];
    }

    Number Number::dop_code() const noexcept{
        Number rev;
        try {
            rev.data = new char[len + 1];
        }catch (std::bad_alloc const &err){
            rev.len = 0;
            rev.data = nullptr;
            return rev;
        }
        this->sign() == '0' ? rev.data = copy(data, rev.data, len) : rev.data = cope_rev(data, rev.data, len);
        rev.len = len;
        return rev;
    }

    char *cope_rev(char const a[], char b[], int len) noexcept{ // заполнение для дополнительного кода
        bool flag = true; // запоминаем единицу, которую хотим добавить, чтобы 2 раза не проходить массив
        int k = 0, i;
        for (i = 1; i <= len; i++){
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
        b[0] = a[0];
        return b;
    }

    Number& Number::operator+=(Number const &a) noexcept{
        Number a_dop(a.dop_code()), b_dop(this->dop_code());
        delete [] data;
        try {
            a.len > this->len ? data = new char[a.len + 2] : data = new char[this->len +2]; // с запасом на переполнение
        }catch (std::bad_alloc const &err){
            len = 0;
            data = nullptr;
            return *this;
        }
        data = bit_sum(a_dop.data, b_dop.data, this->data, a.len, this->len, this->len);
        if (this->sign() == '1'){
            data = cope_rev(this->data, this->data, this->len);
        }
        return *this;
    }

    char *bit_sum(char const *a, char const *b, char *s, int len_a, int len_b, int &len) noexcept{
        bool flag = false; // флаг для единицы
        int len_f, i;
        len_a > len_b ? len_f = len_b : len_f = len_a;
        for (i = 1; i <= len_f; i++){ // суммируем без битового знаком и до разряда меньшего числа
            one_bit_sum(a[i], b[i], s[i], flag);
        }
        len_a > len_b ? s = dop_add(a, b, s, len_a, i, flag) : s = dop_add(b, a, s, len_b, i, flag); // расширение до одного разряда
        if ((flag && a[0] == '0' && b[0] == '0') || (!flag && a[0] == '1' && b[0] == '1')){ // хотим расширить разрядную сетку
            if (a[0] == '0') {
                s[i] = '1';
                flag = false;
            } else {
                s[i] = '0';
                flag = true;
            }
        } else{
            i--;
        }
        one_bit_sum(a[0], b[0], s[0], flag); // считаем знак числа
        len = i;
        return s;
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

    char *dop_add(char const *a, char const *b, char *s, int const &len, int &i, bool &flag) noexcept{
        if (b[0] == '0'){ // суммируем в зависимости от знака меньшего числа
            for (; i <= len; i++){
                one_bit_sum('0', a[i], s[i], flag);
            }
        } else{
            for (; i <= len; i++){
                one_bit_sum('1', a[i], s[i], flag);
            }
        }
        return s;
    }

    Number operator+(Number num1, Number const &num2) noexcept{
        return num1+=num2;
    }

    Number::Number(Number const &a) noexcept{
        try {
            data = new char[a.len + 1];
        }catch (std::bad_alloc const &err){
            len = 0;
            data = nullptr;
        }
        data = copy(a.data, data, a.len);
        len = a.len;
    }

    Number& Number::operator=(Number const &a) noexcept{ // нужен чтобы можно было переприсваивать результат суммы
        if (this != &a){ // проверяем, не является ли это тем же самым
            try {
                data = new char[a.len + 1];
            }catch (std::bad_alloc const &err){
                len = 0;
                data = nullptr;
                return *this;
            }
            data = copy(a.data, data, a.len);
            len = a.len;
        }
        return *this;
    }

    Number Number::operator--(int) noexcept{
        Number x(*this);
        Number a(-1);
        *this += a;
        return x;
    }

    Number& Number::operator++() noexcept{
        Number a("1");
        *this += a;
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, Number const &num) noexcept{
        if (num.len != 0){
            os << num.data[0];
            for (int i = num.len; i >= 1; i--) {
                os << num.data[i];
            }
            os << std::endl;
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Number &num) noexcept{
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

    Number::Number(Number && a) noexcept : len(a.len), data(a.data){
        a.len = 0;
        a.data = nullptr;
    }

    Number& Number::operator=(Number && a) noexcept{
        delete [] data;
        data = a.data;
        len = a.len;
        a.data = nullptr;
        a.len = 0;
        return *this;
    }
}
