#include "area067_14.h"

MATCH void func_801F39AC(void) {
    s32   index;
    void* cell;

    cell  = (void*)AREA_WORK_WINDOW;
    index = 0;
    do {
        FIELD(s16, cell, 0xCu) = 0;
        index += 1;
        cell += 0xE;
    } while ((u32)(index & BYTE_MASK) < 0x80U);
}
