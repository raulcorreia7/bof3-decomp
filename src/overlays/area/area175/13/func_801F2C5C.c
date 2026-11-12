#include "area175_13.h"

MATCH void func_801F2C5C(void) {
    u8* spin;
    s32 i;

    spin = (u8*)AREA_WORK;
    i    = 0;
    do {
        Area_InitSpin(spin);
        i += 1;
        spin += 0x2C;
    } while ((i & BYTE_MASK) < 0x20U);
    g_Task->timer = 0;
    g_Task->header.mode += 1;
}
