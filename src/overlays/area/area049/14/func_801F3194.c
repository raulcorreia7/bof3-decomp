#include "area049_14.h"

MATCH s32 func_801F3194(s32 x, s32 y) {
    s32 i;
    s32 off;
    u8* mode;

    i    = 0;
    x    = x & BYTE_MASK;
    y    = y & BYTE_MASK;
    mode = &g_Game.members[0].facing;
    off  = 0;
    for (; i < 9; i++, off += 4) {
        if (x == D_801F5CDC[off] && y == D_801F5CDD[off] && D_801F5CDE[off] == *mode) {
            break;
        }
    }
    if (i == 9) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F5CDF[i * 4]);
    Scene_StartToggleLock(0xF);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
    return 1;
}
