#include "area047_13.h"

MATCH void func_801F3298(void) {
    s32   index;
    void* cell;

    cell  = (void*)AREA_WORK;
    index = 0;
    do {
        FIELD(s8, cell, 0x14u) = 0;
        index += 1;
        cell += 0x18;
    } while ((u32)(index & BYTE_MASK) < 0x10U);
}
