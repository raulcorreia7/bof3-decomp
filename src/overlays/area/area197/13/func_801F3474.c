#include "area197_13.h"

MATCH void func_801F3474(void) {
    s32 i;
    s8* p;

    p = (s8*)0x800E5C00u;
    i = 0;
    do {
        *p = 0;
        i += 1;
        p += 0x24;
    } while ((i & 0xFFFF) < 0x80U);
}
