#include "Prog1.h"

using namespace Prog1;

int main() {
    Matrix matrix = {0, 0, nullptr}, dop_matrix = {0, 0, nullptr};
    start(matrix);
    std::cout << "First matrix " << std::endl;
    print(matrix);
    dop_matrix = additional_task(matrix);
    std::cout << "Second matrix " << std::endl;
    print_not_rectangular(dop_matrix);
    erase(dop_matrix);
    erase(matrix);
    return 0;
}
