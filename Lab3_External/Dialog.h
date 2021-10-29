//
// Created by User on 28.10.2021.
//

#ifndef LAB3_EXTERNAL_DIALOG_H
#define LAB3_EXTERNAL_DIALOG_H

#include "Vector.h"
#include <vector>

void dialog();
std::vector<int> orthogonality(Prog3::Vector &vec1, Prog3::Vector &vec2);
int neighbor(Prog3::Vector &vec1, Prog3::Vector &vec2);
bool merger(Prog3::Vector &vec1, Prog3::Vector &vec2);
void input(Prog3::Vector &vec1, Prog3::Vector &vec2);





#endif //LAB3_EXTERNAL_DIALOG_H
