#include <iostream>
#include "time.h"

int main() {
    while (true) {
        clock_t c = clock();
        std::cout << c << std::endl;
    }
    return 0;
}