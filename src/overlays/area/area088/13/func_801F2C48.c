#include "area088_13.h"

MATCH void func_801F2C48(void) {
    s32 i;

    i                   = 0;
    g_Task->pos.x.fixed = 0x10000;
    g_Task->pos.y.fixed = 0x250000;
    g_Task->pos.z.fixed = 0x03800000;
    MATCH_FAKE_BARRIER(); /* FAKE: keeps the D_800E4B3E store below the work stores */
    D_800E4B3E = 0x60;
    do {
        func_801F2F28((u8*)AREA_WORK);
        i += 1;
    } while ((i & 0xFF) < 0x20U);
    g_Task->unk_09 = 0;
    g_Task->header.mode += 1;
}
