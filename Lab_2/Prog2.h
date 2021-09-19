//
// Created by User on 11.09.2021.
//

#ifndef LAB_2_PROG2_H
#define LAB_2_PROG2_H

#include <iostream>

namespace Prog2 {

    enum Type{ // перечисляемый тип для типа фигуры
        ELLIPTICAL,
        TWO_CIRCLE,
        LEMNISCATA_BERNOULLI,
        HYPERBOLIC
    };

    class LemniscataButa {
    public:
        explicit LemniscataButa(double c = 0, double m = 0) : c(c), m(m), polar_cos(0), polar_sin(0) {
            set_polar(); // коэффициенты могут принимать любые значения, при отрицательных поворот на пи/2
        }

        ~LemniscataButa() = default;

        double get_c() const { // часть методов реализованы в h файле, т.к. они небольшие
            return c;
        }

        double get_m() const {
            return m;
        }

        void set_c(double const &c_) {
            c = c_;
            set_polar(); // изменяем полярные координаты
        }

        void set_m(double const &m_) {
            m = m_;
            set_polar();
        }

        double get_polar_cos() const{
            return polar_cos;
        }

        double get_polar_sin() const{
            return polar_sin;
        }

        Type type() const;
        double area() const;
        double radius(double fi) const;
        void get_in_polar(char s[], int len) const;
    private:
        void set_polar();
        double c; // Т.к. коэффициенты могут быть нецелыми, например -0.5
        double m;
        double polar_cos; // коэф перед косинусом в полярных координатах
        double polar_sin; // перед синусом
    };

    void dialog();
    bool is_equal(double const &x, double const &y);
}

#endif //LAB_2_PROG2_H
