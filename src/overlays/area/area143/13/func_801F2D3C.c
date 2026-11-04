#include "area143_13.h"

MATCH void func_801F2D3C(void) {
    s32 index;
    s8* row;
    u8* tail;

    row   = (s8*)AREA_WORK;
    index = 0;
    tail  = (u8*)(AREA_WORK + 2);
    do {
        *row             = 0;
        *(s8*)(tail - 1) = 0;
        *(s8*)tail       = 0;
        tail += 0x18;
        index += 1;
        row += 0x18;
    } while ((u32)(index & HALF_MASK) < 0x100U);
}
