#include "area130_13.h"

MATCH void func_801F2C60(void) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0x800E4800;
    var_s0 = 0;
    do {
        Area_InitSpin(var_s1);
        var_s0 += 1;
        var_s1 += 0x2C;
    } while ((u32)(var_s0 & 0xFF) < 0x20U);
    g_SpadWork->unk_09 = 0;
    g_SpadWork->unk_01 += 1;
}
