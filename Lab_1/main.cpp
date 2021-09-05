#include "Prog1.h"

using namespace Prog1;

int main() {
    Matrix matrix = {0, 0, nullptr};
    start(matrix);
    std::cout << "First matrix " << std::endl;
    print(matrix);
    erase(matrix);
    /*dop_matrix = Prog1::additional_task(matrix);
    std::cout << "Second matrix " << std::endl;
    Prog1::print(dop_matrix);
    Prog1::erase(dop_matrix);*/
    //Prog1::erase(matrix);
    return 0;
}
