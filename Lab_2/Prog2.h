//
// Created by User on 11.09.2021.
//

#ifndef LAB_2_PROG2_H
#define LAB_2_PROG2_H

#include <iostream>

namespace Prog2 {

    class LemniscataButa {
    public:
        explicit LemniscataButa(double c = 0, double m = 0) : c(c), m(m), polar_cos(0), polar_sin(0) {
            set_polar(); // коэффициенты могут принимать любые значения, при отрицательных поворот на пи/2
        }

        ~LemniscataButa() = default;

        double get_c() const {
            return c;
        }

        double get_m() const {
            return m;
        }

        void set_c(int const &c_) {
            c = c_;
            set_polar(); // изменяем полярные координаты
        }

        void set_m(int const &m_) {
            m = m_;
            set_polar();
        }

        double get_polar_cos() const{
            return polar_cos;
        }

        double get_polar_sin() const{
            return polar_sin;
        }

        std::string type() const;
        double area() const;
        double radius(int fi) const;
        char* get_in_polar() const;
    private:
        void set_polar();
        double c; // Т.к. коэффициенты могут быть нецелыми, например -0.5
        double m;
        double polar_cos; // коэф перед косинусом в полярных координатах
        double polar_sin; // перед синусом
    };

    void dialog();
}

#endif //LAB_2_PROG2_H
