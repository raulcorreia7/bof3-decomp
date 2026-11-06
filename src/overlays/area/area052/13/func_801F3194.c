#include "area052_13.h"

MATCH void func_801F3194(void) {
    s32   index;
    void* cell;

    cell  = (void*)AREA_WORK;
    index = 0;
    do {
        FIELD(s8, cell, 0x15u) = 0;
        index += 1;
        cell += 0x18;
    } while ((index & 0xFF) < 0x10U);
}
