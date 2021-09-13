#include "Prog2.h"

using namespace Prog2;

int main() {

    LemniscataButa line(0,10);
    std::cout << line.radius(60) << std::endl;
    std::cout << line.get_in_polar();
    return 0;
}
