#include "area112_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3A14(s32 x, s32 y) {
    s32 i;
    s32 off;
    s32 j;
    u8* mode;

    i    = 0;
    x    = x & BYTE_MASK;
    y    = y & BYTE_MASK;
    mode = &g_Game.members[0].facing;
    off  = 0;
    for (; i < 4; i++, off += 4) {
        if (x == D_801F4908[off] && y == D_801F4909[off] && *mode != FACING_RIGHT) {
            break;
        }
    }
    if (i == 4) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, D_801F490B[i * 4]) != 0) {
        return 0;
    }
    if ((func_801F3CF0() & BYTE_MASK) != 0) {
        Game_SetScriptActive();
        g_SceneEventMode      = 10;
        g_SceneEventStep      = 10;
        g_SceneEventSelection = 0x15;
        return 0;
    }
    j = 0;
    do {
        if ((D_801F490A[off] >> j) & 1) {
            if (j < 4) {
                SYS_ClearFlag(g_SceneEventFlags, D_801F4928[j & 3]);
            } else {
                SYS_SetFlag(g_SceneEventFlags, D_801F4928[j & 3]);
            }
        }
        j++;
    } while (j < 8);
    SYS_SetFlag(g_SceneEventFlags, D_801F490B[i * 4]);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
    func_8019ABB0(0xF);
    return 1;
}
#else
INCLUDE_ASM(func_801F3A14);
#endif
