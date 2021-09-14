//
// Created by User on 11.09.2021.
//

#include "Prog2.h"
#include <cmath>
#include <cstring>
#include <cstdio>

namespace Prog2 {

    std::string LemniscataButa::type() const {
        double mn = 2 * m * m;
        if (c > mn) {
            return "elliptical"; // эллиптический тип
        } else if (c == mn) {
            return "two circle"; // 2 окружности
        } else if (c == 0) {
            return "lemniscata bernoulli"; // лемнискат Бернулли
        } else {
            return "hyperbolic"; // гиперболический
        }
    }

    double LemniscataButa::area() const {
        double const pi = 3.14;
        double mn = 2 * m * m;
        double a = mn + c, b, a_, b_;
        if (c > mn) { // Эллиптический тип (легче сравнивать именно числа, т.к. они нужны для вычисления)
            b = c - mn;
            return ( (pi / 2) * (a + b));
        } else if (c == mn) {
            return mn * pi; // площадь 2 окружностей (радиус m, проверял)
        } else if (c == 0) { // площадь лемниската Бернулли, где коэффициент a^2 = 2*m*m;
            return mn;
        } else { // гиперболический тип
            b = mn - c;
            if (a < 0 || b < 0){
                return 0;
            } else {
                a_ = sqrt(a), b_ = sqrt(b);
                return ((a - b) / 2 * atan(a_ / b_) + a_ * b_ / 2);
            }
        }
    }

    void LemniscataButa::set_polar() {
        double mn = 2 * m * m;
        if (c > mn){ // из википедии (эллиптическая)
            polar_cos = mn + c;
            polar_sin = c - mn;
        } else if (c == 0){ // лемнискат Бернулли
            polar_cos = mn;
            polar_sin = 0;
        }
        else if (c == mn){ // сам выводил для 2 окружностей
            polar_cos = -2*m;
            polar_sin = 0;
        } else{ // гиперболическая
            polar_cos = mn + c;
            polar_sin = -(mn - c);
        }
    }

    double LemniscataButa::radius(int fi) const {
        double const rad = 3.14 / 180; // Для перевода в радианы, т.к. функция считает именно в радианах
        if (polar_cos == 0 && polar_sin == 0){
            return 0;
        }
        std::string type = this->type();
        double cos_fi = cos(fi * rad), sin_fi = sin(fi * rad), sum;
        if (type == "two circle"){
            return -polar_cos*cos_fi;
        } else if (type == "lemniscata bernoulli"){
            sum = polar_cos*cos(2*fi * rad);
            if (sum <= 0){
                return 0;
            } else{
                return sqrt(sum);
            }
        } else{ // Сразу для 2 случаев, т.к. различие только в коэффициенте
            sum = polar_cos*cos_fi*cos_fi + polar_sin*sin_fi*sin_fi;
            if (sum <= 0){
                return 0;
            } else{
                return sqrt(sum);
            }
        }
    }

    char *LemniscataButa::get_in_polar() const { // r^2 = " "*(cos(fi))^2 + " "*(sin(fi))^2
        std::string type = this->type();
        char s1[] = "r^2 = *(cos(fi))^2 + *(sin(fi))^2";
        unsigned long l = strlen(s1) + 1; // кол-во элементов с нуль байтом
        char num[20];
        sprintf(num, "%.2f", polar_cos);
        l += strlen(num);
        sprintf(num, "%.2f", polar_sin);
        l += strlen(num);
        char *s;
        try {
            s = new char[l];
        } catch (std::bad_alloc const &a) {
            std::cout << a.what() << std::endl;
            std::cout << "Can`t allocate memory!" << std::endl;
            return nullptr;
        }
        if (polar_cos == 0){
            sprintf(s, "r^2 = 0");
        } else {
            sprintf(s, "r^2 = %.2f*(cos(fi))^2", polar_cos);
            int k = strlen(s);
            if (type == "elliptical") {
                sprintf(s + k, " + %.2f*(sin(fi))^2", polar_sin);
            } else if (type == "hyperbolic") {
                sprintf(s + k, " - %.2f*(sin(fi))^2", -polar_sin);
            }
        }
        return s;
    }

    void dialog(){
        int m, c;
        std::cout << "Set first parameter(m)" << std::endl;
        std::cin >> c;
        std::cout << "Set second parameter(m)" << std::endl;
        std::cin >> m;
        LemniscataButa line(c, m); // вызываем конструктор с данными параметрами
        while (true) {
            int i = 1;
            std::string functions[] = {"Type", "Area", "Polar coordinates", "radius", "formula", "change parameters"};
            std::cout << "Input 0 to quit" << std::endl;
            for (std::string const &a: functions) { // выводим на экран
                std::cout << i << ") " << a << std::endl;
                i++;
            }
            std::cout << "Input number of command" << std::endl;
            std::cin >> i;
            if (i == 0) {
                break;
            }
            switch (i) {
                case 1:std::cout << line.type();
                    break;
                case 2:std::cout << line.area();
                    break;
                case 3:std::cout << "Cos parameter: " << line.get_polar_cos() << "\nSin parameter: " << line.get_polar_sin();
                    break;
                case 4: {
                    int fi;
                    std::cout << "Input angle : ";
                    std::cin >> fi;
                    std::cout << line.radius(fi);
                    break;
                }
                case 5: {
                    char *s = line.get_in_polar();
                    std::cout << s << std::endl;
                    delete[] s;
                    break;
                }
                case 6:{
                    int m_, c_;
                    std::cout << "Input new c-parameter" << std::endl;
                    std::cin >> c_;
                    std::cout << "Input new m-parameter" << std::endl;
                    std::cin >> m_;
                    line.set_c(c_), line.set_m(m_);
                    break;
                }
                default:std::cout << "We can`t find this command!";
                    break;
            }
            std::cout << std::endl;
        }
    }
}
