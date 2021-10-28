//
// Created by User on 28.10.2021.
//

#include "Dialog.h"

void dialog(){
    int option, k = 0;
    bool flag = true;
    Prog3::Vector vec1, vec2;
    std::string menu[] = {"Выход", "Проверка векторов на ортогональность"};
    while (flag){
        for (std::string const &i : menu){
            std::cout << k << ") " << i << std::endl;
            k++;
        }
        std::cout << "Введите номер команды" << std::endl;
        std::cin >> option;
        switch (option) {
            case 0:{
                flag = false;
                break;
            }
            case 1:{
                std::cout << "Введите значения векторов\nПервый: ";
                std::cin >> vec1;
                std::cout << "Второй: ";
                std::cin >> vec2;
                if(orthogonality(vec1, vec2)){
                    std::cout << "Вектора ортогональны" << std::endl;
                } else{
                    std::cout << "Вектора не ортогональны" << std::endl;
                }
                break;
            }
            default:{
                std::cout << "Такой команды нет!";
                break;
            }
        }
    }
}

bool orthogonality(Prog3::Vector const &vec1, Prog3::Vector const &vec2){
    int size = vec1.get_size() >= vec2.get_size() ? vec2.get_size() : vec1.get_size();
    for (int i = 0; i < size; i++){

    }
}
