#include "Prog1.h"

using namespace Prog1;

int main() {
    Matrix matrix = {0, 0, nullptr}, dop_matrix = {0, 0, nullptr};
    bool flag = start(matrix);
    if (!flag){
        std::cout << "Incorrect matrix" << std::endl;
        erase(matrix); // удаление матрицы
        return 1;
    }
    std::cout << "First matrix " << std::endl;
    print(matrix);
    dop_matrix = additional_task(matrix);
    std::cout << "Second matrix " << std::endl;
    print_not_rectangular(dop_matrix);
    erase(dop_matrix);
    erase(matrix);
    return 0;
}
