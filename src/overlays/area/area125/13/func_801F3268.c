#include "area125_13.h"

MATCH void func_801F3268(u8 count) {
    u8 order[16];
    u8 i;
    u8 a;
    u8 b;
    u8 tmp;

    for (i = 0; i < 16; i++) {
        order[i] = i;
    }
    for (i = 0; i < 16; i++) {
        a        = RANDOM_MASK(0xF);
        b        = rand() & 0xF;
        tmp      = order[a];
        order[a] = order[b];
        order[b] = tmp;
    }
    for (i = 0; i < count; i++) {
        func_801F31B0(order[i]);
    }
}
