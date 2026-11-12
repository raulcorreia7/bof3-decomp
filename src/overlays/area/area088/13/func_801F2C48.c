#include "area088_13.h"

MATCH void func_801F2C48(void) {
    s32 i;

    i                   = 0;
    g_Task->pos.x.fixed = TO_COORD(1);
    g_Task->pos.y.fixed = TO_COORD(37);
    g_Task->pos.z.fixed = 0x03800000;
    FAKE_BARRIER(); /* FAKE: keeps the D_800E4B3E store below the work stores */
    D_800E4B3E = 0x60;
    do {
        func_801F2F28((u8*)AREA_WORK);
        i += 1;
    } while ((i & BYTE_MASK) < 0x20U);
    g_Task->timer = 0;
    g_Task->header.mode += 1;
}
