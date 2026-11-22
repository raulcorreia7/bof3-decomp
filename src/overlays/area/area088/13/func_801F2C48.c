#include "area088_13.h"

MATCH void func_801F2C48(void) {
    s32 i;

    i                        = 0;
    TASK(Actor)->pos.x.fixed = TO_COORD(1);
    TASK(Actor)->pos.y.fixed = TO_COORD(37);
    TASK(Actor)->pos.z.fixed = 0x03800000;
    FAKE_BARRIER(); /* FAKE: keeps the D_800E4B3E store below the work stores */
    D_800E4B3E = 0x60;
    do {
        Trail_Update((Trail*)AREA_WORK);
        i += 1;
    } while ((i & BYTE_MASK) < 0x20U);
    TASK(Actor)->timer = 0;
    TASK(Actor)->header.mode += 1;
}
