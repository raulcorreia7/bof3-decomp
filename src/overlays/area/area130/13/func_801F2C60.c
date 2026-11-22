#include "area130_13.h"

MATCH void func_801F2C60(void) {
    s32 i;
    s32 work;

    work = AREA_WORK;
    i    = 0;
    do {
        Area_InitSpin(work);
        i += 1;
        work += 0x2C;
    } while ((i & BYTE_MASK) < 0x20U);
    TASK(Actor)->timer = 0;
    TASK(Actor)->header.mode += 1;
}
