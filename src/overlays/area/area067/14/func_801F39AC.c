#include "area067_14.h"

MATCH void func_801F39AC(void) {
    s32   index;
    void* cell;

    cell  = (void*)AREA_WORK;
    index = 0;
    do {
        FIELD(s16, cell, 0xCu) = 0;
        index += 1;
        cell += 0xE;
    } while ((index & 0xFF) < 0x80U);
}
