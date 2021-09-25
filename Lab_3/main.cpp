#include "Prog3.h"

using namespace Prog3;

int main() {
    Number i(10), f(6);
    Number k = sum(i, f);
    i.output();
    f.output();
    k.output();

    return 0;
}
