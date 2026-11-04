#include "area080_13.h"

MATCH void func_801F3834(void) {
    s32 index;

    D_801F44A4 = (s8*)(AREA_WORK + 0x6C);
    index      = 0;
    do {
        index += 1;
        *D_801F44A4 = 0;
    } while ((u32)(index & BYTE_MASK) < 8U);
}
