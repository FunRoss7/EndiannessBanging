#include "stdio.h"
#include <stdint.h>
#include "StaticTemplate.h"

void TrivialCase() {
    printf("Trivial Case:\n");
    struct Trivial1 {
        #if __ORDER_LITTLE_ENDIAN__
        uint32_t f5 : 8;
        uint32_t f4 : 2;
        uint32_t f3 : 12;
        uint32_t f2 : 2;
        uint32_t f1 : 8;
        uint8_t b1;
        #elif __ORDER_BIG_ENDIAN__
        uint8_t b1;
        uint32_t f1 : 8;
        uint32_t f2 : 2;
        uint32_t f3 : 12;
        uint32_t f4 : 2;
        uint32_t f5 : 8;
        #endif

    };

    struct LessTrivial2 {
        #if __ORDER_LITTLE_ENDIAN__
        uint8_t b2;
        uint16_t a1[2]; // Handling this sucks, need the order reversed
        uint8_t b1;
        #elif __ORDER_BIG_ENDIAN__
        uint8_t b1;
        uint16_t a1[2]; // Completely fine in BE
        uint8_t b2;
        #endif
    };
}

int main () {
    TrivialCase();
    return 0;
}