#include "Console.h"

void game() noexcept{
    App start;
    do{
        start.buy();
    } while (!start.upload());
    start.gameplay();
}

int main() {
    game();
    return 0;
}