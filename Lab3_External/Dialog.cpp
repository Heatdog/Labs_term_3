//
// Created by User on 28.10.2021.
//

#include "Dialog.h"

void dialog(){
    int option, k = 0;
    bool flag = true;
    std::vector<int> mass;
    Prog3::Vector vec1, vec2;
    std::string menu[] = {"Выход", "Проверка на ортогональность", "Проверка на пересечение", "Проверка на смежность",
                          "Проверка на соседство", "Проверка на поглощение"};
    while (flag){
        for (std::string const &i : menu){
            std::cout << k << ") " << i << std::endl;
            k++;
        }
        k = 0;
        std::cout << "Введите номер команды" << std::endl;
        std::cin >> option;
        switch (option) {
            case 0:{
                flag = false;
                break;
            }
            case 1:{
                try {
                    input(vec1, vec2);
                }catch (std::exception const &err){
                    return;
                }
                mass = orthogonality(vec1, vec2);
                if(!mass.empty()){
                    std::cout << "Вектора ортогональны по компонентам: ";
                    for (int const i : mass){
                        std::cout << i << " ";
                    }
                    std::cout << std::endl;
                } else{
                    std::cout << "Вектора не ортогональны" << std::endl;
                }
                mass.clear();
                break;
            }
            case 2:{
                try {
                    input(vec1, vec2);
                }catch (std::exception const &err){
                    return;
                }
                mass = orthogonality(vec1, vec2);
                if(mass.empty()){
                    std::cout << "Вектора пересекаются" << std::endl;
                } else{
                    std::cout << "Вектора не пересекаются" << std::endl;
                }
                mass.clear();
                break;
            }
            case 3:{
                try {
                    input(vec1, vec2);
                }catch (std::exception const &err){
                    return;
                }
                mass = orthogonality(vec1, vec2);
                if (mass.size() == 1){
                    std::cout << "Вектора смежны" << std::endl;
                } else{
                    std::cout << "Вектора не смежны" << std::endl;
                }
                mass.clear();
                break;
            }
            case 4:{
                try {
                    input(vec1, vec2);
                }catch (std::exception const &err){
                    return;
                }
                int result = neighbor(vec1, vec2);
                if (result != 0){
                    std::cout << "Вектора являются соседними по компоненте " << result << std::endl;
                } else{
                    std::cout << "Вектора не являются соседними" << std::endl;
                }
                break;
            }
            case 5:{
                try {
                    input(vec1, vec2);
                }catch (std::exception const &err){
                    return;
                }
                if (merger(vec1, vec2)){
                    std::cout << "Первый вектор поглощает второй" << std::endl;
                } else{
                    std::cout << "Первый вектор не поглощает второй" << std::endl;
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

std::vector<int> orthogonality(Prog3::Vector &vec1, Prog3::Vector &vec2){ // проверка на ортогональность
    std::vector<int> mass;
    const char *data_1 = vec1.get_c(), *data_2 = vec2.get_c();
    int size = vec1.get_size() >= vec2.get_size() ? vec2.get_size() : vec1.get_size();
    for (int i = 0; i < size; i++){
        if ((data_1[i] == '0' && data_2[i] == '1') || (data_2[i] == '0' && data_1[i] == '1')){
            mass.push_back(i+1);
        }
    }
    return mass;
}

int neighbor(Prog3::Vector &vec1, Prog3::Vector &vec2){
    const char *data_1 = vec1.get_c(), *data_2 = vec2.get_c();
    int size = vec1.get_size() >= vec2.get_size() ? vec2.get_size() : vec1.get_size();
    int k = 0, result;
    for (int i = 0; i < size; i++){
        if (data_1[i] != data_2[i]){
            k++;
            result = i;
        }
        if (k == 2){
            return 0;
        }
    }
    return k == 1 ? result+1 : 0;
}

bool merger(Prog3::Vector &vec1, Prog3::Vector &vec2){
    const char *data_1 = vec1.get_c(), *data_2 = vec2.get_c();
    for (int i = 0; i < vec1.get_size(); i++){
        if (data_1[i] != 'x' && data_1[i] != 'X'){
            if (data_1[i] != data_2[i]){
                return false;
            }
        }
    }
    return true;
}

void input(Prog3::Vector &vec1, Prog3::Vector &vec2){
    std::cout << "Введите значения векторов\nПервый: ";
    std::cin >> vec1;
    std::cout << "Второй: ";
    std::cin >> vec2;
}