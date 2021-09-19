//
// Created by User on 11.09.2021.
//

#include "Prog2.h"
#include <cmath>
#include <cstring>
#include <cstdio>


namespace Prog2 {

    Type LemniscataButa::type() const {  // перечислимый тип сделать (+)
        double mn = 2 * m * m;
        if (c > mn) {
            return ELLIPTICAL; // эллиптический тип
        } else if (is_equal(c, mn)) { // для операторов сравнения > и < оставим погрешность
            return TWO_CIRCLE; // 2 окружности
        } else if (is_equal(c, 0)) {
            return LEMNISCATA_BERNOULLI; // лемнискат Бернулли
        } else {
            return HYPERBOLIC; // гиперболический
        }
    }

    double LemniscataButa::area() const {
        double mn = 2 * m * m;
        double a = mn + c, b, a_, b_;
        if (c > mn) { // Эллиптический тип (легче сравнивать именно числа, т.к. они нужны для вычисления)
            b = c - mn;
            return ( (M_PI / 2) * (a + b));
        } else if (is_equal(c, mn)) {
            return mn * M_PI; // площадь 2 окружностей (радиус m, проверял)
        } else if (is_equal(c, 0)) { // площадь лемниската Бернулли, где коэффициент a^2 = 2*m*m;
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
        } else if (is_equal(c, 0)){ // лемнискат Бернулли
            polar_cos = mn;
            polar_sin = 0;
        } else if (is_equal(c, mn)){ // сам выводил для 2 окружностей
            polar_cos = -2*m;
            polar_sin = 0;
        } else{ // гиперболическая
            polar_cos = mn + c;
            polar_sin = -(mn - c);
        }
    }

    double LemniscataButa::radius(double fi) const { // дабл (больше тестов на отрицательное)
        double const rad = M_PI / 180; // Для перевода в радианы, т.к. функция считает именно в радианах
        if (is_equal(polar_cos, 0) && is_equal(polar_sin, 0)){
            return 0;
        }
        Type type = this->type();
        double cos_fi = cos(fi * rad), sin_fi = sin(fi * rad), sum;
        if (type == TWO_CIRCLE){
            return std::fabs(polar_cos*cos_fi); // возвращаем модуль
        } else if (type == LEMNISCATA_BERNOULLI){
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

    void LemniscataButa::get_in_polar(char s[], int len) const { // r^2 = " "*(cos(fi))^2 + " "*(sin(fi))^2 (передавать буффер)
        Type type = this->type();
        char s1[] = "r^2 = *(cos(fi))^2 + *(sin(fi))^2";
        unsigned long l = strlen(s1) + 1; // кол-во элементов с нуль байтом
        char num[20];
        sprintf(num, "%.2f", polar_cos); // записываем во временный буффер
        l += strlen(num);
        sprintf(num, "%.2f", polar_sin);
        l += strlen(num);
        if (l > len){
            throw std::out_of_range("Can`t input in massive! Out of range");
        }
        if (polar_cos == 0){
            sprintf(s, "r^2 = 0");
        } else {
            sprintf(s, "r^2 = %.2f*(cos(fi))^2", polar_cos);
            int k = strlen(s);
            if (type == ELLIPTICAL) {
                sprintf(s + k, " + %.2f*(sin(fi))^2", polar_sin);
            } else if (type == HYPERBOLIC) {
                sprintf(s + k, " - %.2f*(sin(fi))^2", -polar_sin);
            }
        }
    }

    void dialog(){
        double m, c;
        std::string const error = "Input error!";
        bool flag = true;
        std::cout << "Set first parameter(c)" << std::endl;
        if (!(std::cin >> c)){
            std::cout << error << std::endl;
            return;
        }
        std::cout << "Set second parameter(m)" << std::endl;
        if (!(std::cin >> m)){
            std::cout << error << std::endl;
            return;
        }
        LemniscataButa line(c, m); // вызываем конструктор с данными параметрами
        while (flag) {
            int i = 0;
            std::string functions[] = {"Quit", "Type", "Area", "Polar coordinates", "radius", "formula", "change parameters"};
            std::string Type[] = {"Elliptical", "Two circle", "Lemniscata Bernoulli", "Hyperbolic"};
            for (std::string const &a: functions) { // выводим на экран
                std::cout << i << ") " << a << std::endl;
                i++;
            }
            std::cout << "Input number of command" << std::endl;
            if (!(std::cin >> i)) {
                std::cout << error << std::endl;
                return;
            }
            switch (i) {
                case 0:{
                    flag = false;
                    break;
                }
                case 1:{
                    std::cout << Type[line.type()];
                    break;
                }
                case 2:std::cout << line.area();
                    break;
                case 3:std::cout << "Cos parameter: " << line.get_polar_cos() << "\nSin parameter: " << line.get_polar_sin();
                    break;
                case 4: {
                    double fi;
                    std::cout << "Input angle : ";
                    if (!(std::cin >> fi)){
                        std::cout << error << std::endl;
                        return;
                    }
                    std::cout << line.radius(fi);
                    break;
                }
                case 5: {
                    int const len = 100;
                    char s1[len]; //проверить на выход за границу массива
                    try { // закидываем все операции с потенциальной ошибкой (stack unwinding)
                        line.get_in_polar(s1, len);
                        std::cout << s1 << std::endl;
                    }catch (std::exception const &a){ // обрабатываем исключение на переполнение массива
                        std::cout << a.what() << std::endl;
                    }
                    break;
                }
                case 6:{
                    double m_, c_;
                    std::cout << "Input new c-parameter" << std::endl;
                    if (!(std::cin >> c_)){
                        std::cout << error << std::endl;
                        return;
                    }
                    std::cout << "Input new m-parameter" << std::endl;
                    if (!(std::cin >> m_)){
                        std::cout << error << std::endl;
                        return;
                    }
                    line.set_c(c_), line.set_m(m_);
                    break;
                }
                default:std::cout << "We can`t find this command!";
                    break;
            }
            std::cout << std::endl;
        }
    }

    bool is_equal(double const &x, double const &y){ // Функция Дональда Кнута (работает через процентное отношение наиб. числа)
        return fabs(x - y) <= ( (fabs(x) < fabs(y) ? fabs(x) : fabs(y)) * 0.00001);
    }
}
