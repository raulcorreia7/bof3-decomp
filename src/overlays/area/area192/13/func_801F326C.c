#include "area192_13.h"

#ifdef NON_MATCHING
NON_MATCHING u16 func_801F326C(u8 character_id) {
    u8  area;
    u8  slot;
    u8  fatigue;
    u8  row;
    s32 base;

    for (row = 0; row < 5; row++) {
        if (D_801F3878[row] == character_id) {
            break;
        }
    }
    area = D_80144F56;
    base = row * 9;
    row  = base;
    if (area >= 9) {
        area = 8;
    }
    slot    = g_CharSlot[character_id];
    fatigue = g_Characters[slot].fatigue;
    if (SYS_TestFlag(D_80144EF8, 0xA) != 0) {
        return func_801F33E4(row, character_id, area, fatigue);
    }
    if (fatigue >= 8) {
        row = base + 8;
    } else if (fatigue < 5 || area >= 7) {
        row = base + D_801F3880[area];
    } else {
        row = base + 7;
    }
    if (SYS_TestFlag(g_SceneFlags, 2) != 0) {
        return D_801F3848[row];
    }
    return D_801F3818[row];
}
#else
INCLUDE_ASM(func_801F326C);
#endif
