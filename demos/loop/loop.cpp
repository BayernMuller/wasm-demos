#include <emscripten/emscripten.h>
#include <iostream>

extern "C" {
    unsigned long long EMSCRIPTEN_KEEPALIVE sum_of_one_to_n(unsigned int n) {
        unsigned long long sum = 0;
        for (unsigned int i = 1; i <= n; ++i) {
            sum += i;
        }
        return sum;
    }
}