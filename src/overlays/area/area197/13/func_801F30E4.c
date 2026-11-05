#include "area197_13.h"

MATCH void func_801F30E4(void) {
    s32 i;
    s8* p;

    p = (s8*)AREA_WORK;
    i = 0;
    do {
        *p = 0;
        i += 1;
        p += 0x28;
    } while ((u32)(i & HALF_MASK) < 0x80U);
}
