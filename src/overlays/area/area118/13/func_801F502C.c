#include "area118_13.h"

MATCH s32 func_801F502C(s32 x, s32 y) {
    s32 i;
    s32 off;
    u8* mode;

    i    = 0;
    x    = x & BYTE_MASK;
    y    = y & BYTE_MASK;
    mode = &g_Game.members[0].facing;
    off  = 0;
    for (; i <= 0; i++, off += 4) {
        if (x == D_801F59E0[off] && y == D_801F59E1[off] && D_801F59E2[off] == *mode) {
            break;
        }
    }
    if (i == 1) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F59E3[i * 4]);
    Scene_StartToggleLock(0xF);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
    return 1;
}
