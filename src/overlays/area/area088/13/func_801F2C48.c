#include "area088_13.h"

MATCH void func_801F2C48(void) {
    s32 i;

    i = 0;
    g_SpadWork->x.fixed = 0x10000;
    g_SpadWork->y.fixed = 0x250000;
    g_SpadWork->z.fixed = 0x03800000;
    MATCH_FAKE_BARRIER(); /* FAKE: keeps the D_800E4B3E store below the work stores */
    D_800E4B3E = 0x60;
    do {
        func_801F2F28((u8 *)0x800E4800);
        i += 1;
    } while ((u32) (i & 0xFF) < 0x20U);
    g_SpadWork->unk_09 = 0;
    g_SpadWork->unk_01 += 1;
}
