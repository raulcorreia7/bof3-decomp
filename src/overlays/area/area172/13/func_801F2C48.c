#include "area172_13.h"

MATCH void func_801F2C48(void) {
    u8* first;
    u8* second;
    u8* third;

    first       = TASK(u8);
    first[0x5F] = 0;
    first[0x5E] = 0;
    first[0x5D] = 0;

    second    = TASK(u8);
    second[9] = 0x5A;

    third    = TASK(u8);
    third[1] = 1;
}
