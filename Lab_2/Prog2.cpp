//
// Created by User on 11.09.2021.
//

#include "Prog2.h"
#include <cmath>
#include <cstring>

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
            return pi / 2 * (a + b);
        } else if (c == mn) {
            return mn * pi; // площадь 2 окружностей (радиус m, проверял)
        } else if (c == 0) { // площадь лемниската Бернулли, где коэф a^2 = 2*m*m;
            return mn;
        } else { // гиперболический тип
            b = mn - c;
            a_ = sqrt(a), b_ = sqrt(b);
            return ((a - b) / 2 * atan(a / b) + a_ * b_ / 2);
        }
    }

    LemniscataButa LemniscataButa::polar() const { // возвращаем еще 1 кривую, но уже с полярными коэффициентами
        double mn = 2 * m * m;
        LemniscataButa polar;
        if (c > mn){ // из википедии (эллиптическая)
            polar.c = mn + c;
            polar.m = c - mn;
        } else if (c == mn){ // сам выводил для 2 окружностей
            polar.c = -2*m;
            polar.m = 2*m;
        } else if (c == 0){ // лемнискат Бернулли
            polar.c = mn;
        } else{ // гиперболическая
            polar.c = mn + c;
            polar.m = mn - c;
        }
        return polar;
    }

    void LemniscataButa::set_polar() {
        double mn = 2 * m * m;
        if (c > mn){ // из википедии (эллиптическая)
            polar_cos = mn + c;
            polar_sin = c - mn;
        } else if (c == mn){ // сам выводил для 2 окружностей
            polar_cos = -2*m;
            polar_sin = 0;
        } else if (c == 0){ // лемнискат Бернулли
            polar_cos = mn;
            polar_sin = 0;
        } else{ // гиперболическая
            polar_cos = mn + c;
            polar_sin = -(mn - c);
        }
    }

    double LemniscataButa::radius(int fi) const {
        std::string type = this->type();
        double cos_fi = cos(fi), sin_fi = sin(fi);
        if (type == "two circle"){
            return polar_cos*cos_fi;
        } else if (type == "lemniscata bernoulli"){
            return sqrt(polar_cos*cos(2*fi));
        } else{ // Сразу для 2 случаев, т.к. различие только в коэффициенте
            return sqrt(polar_cos*cos_fi*cos_fi + polar_sin*sin_fi*sin_fi);
        }
    }

    char *LemniscataButa::get_in_polar() const { // r^2 = " "*(cos(fi))^2 + " "*(sin(fi))^2
        std::string type = this->type();
        char s1[] = "r^2 = *(cos(fi))^2 + *(sin(fi))^2";
        unsigned long l1 = strlen(s1) + 1; // кол-во элементов с нуль байтом

    }

}
