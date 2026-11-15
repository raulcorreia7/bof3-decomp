#include "area191_13.h"

#ifdef NON_MATCHING
NON_MATCHING u16 func_801F37AC(s32 slot) {
    u8* flags;
    u8  count;
    u8  mode;
    u8  row;
    s32 i;
    s32 base;

    for (i = 0; (u8)i < 5; i++) {
        if (D_801F4248[(u8)i] == (u8)slot) {
            break;
        }
    }
    flags = &D_80144F56;
    count = *flags;
    base  = (u8)i * 9;

    row = count;
    if (row >= 9) {
        row = 8;
    }

    mode = g_Characters[g_CharSlot[(u8)slot]].fatigue;
    if (SYS_TestFlag(flags - 0x5E, 0xA) != 0) {
        return func_801F3924((u8)base, (u8)slot, (u8)row, (u8)mode);
    }

    if ((u8)mode < 8) {
        if ((u8)mode < 5 || (u8)row >= 7) {
            base += D_801F4250[(u8)row];
        } else {
            base += 7;
        }
    } else {
        base += 8;
    }

    if (SYS_TestFlag(g_SceneFlags, 2) != 0) {
        return D_801F4218[(u8)base];
    }
    return D_801F41E8[(u8)base];
}
#else
INCLUDE_ASM(func_801F37AC);
#endif
