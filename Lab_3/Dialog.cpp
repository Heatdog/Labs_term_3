//
// Created by User on 26.09.2021.
//

#include "Dialog.h"
#include "Prog3.h"

using namespace Static;

void dialog(){
    std::string a, s1, s2;
    std::string const error = "Ошибка ввода!";
    bool flag = true;
    std::cout << "Введите число" << std::endl;
    if (!(std::cin >> a)){
        std::cout << error << std::endl;
        return;
    }
    Number number;
    try {
        number = Number(a);
    }catch (std::invalid_argument const &err1){
        std::cout << err1.what() << std::endl;
    }catch (std::out_of_range const &err2){
        std::cout << err2.what() << std::endl;
    }
    while (flag) {
        int i = 0;
        std::string functions[] = {"Выход", "Вывод числа", "Дополнительный код", "Суммирование", "Знак"};
        for (std::string const &r: functions) { // выводим на экран
            std::cout << i << ") " << r << std::endl;
            i++;
        }
        std::cout << "Введите номер команды" << std::endl;
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
                std::cout << number;
                break;
            }
            case 2: {
                std::cout << number.dop_code();
                break;
            }
            case 3: {
                std::cout << "Введите первое число" << std::endl;
                if (!(std::cin >> s1)){
                    std::cout << error << std::endl;
                    return;
                }
                std::cout << "Введите втрое число" << std::endl;
                if (!(std::cin >> s2)){
                    std::cout << error << std::endl;
                    return;
                }
                Number number1(s1), number2(s2);
                try {
                    number = number1 + number2;
                    std::cout << number;
                }catch (std::out_of_range const &err2){
                    std::cout << err2.what() << std::endl;
                }
                break;
            }
            case 4: {
                std::string name;
                number.sign() == '0' ? name = "число положительное" : name = "число отрицательное";
                std::cout << name;
                break;
            }
            default:std::cout << "Такой команды нет!";
                break;
        }
        std::cout << std::endl;
    }
}