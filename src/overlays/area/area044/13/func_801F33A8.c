#include "area044_13.h"

MATCH s32 func_801F33A8(s32 x, s32 y) {
    s32 i;
    s32 off;
    u8  event;
    u8* mode;

    i    = 0;
    x    = x & BYTE_MASK;
    y    = y & BYTE_MASK;
    mode = &g_Game.members[0].facing;
    off  = 0;
    for (; i < 4; i++, off += 5) {
        if (x == D_801F3FC4[off] && y == D_801F3FC5[off] && (D_801F3FC6[off] & 0xF) == *mode) {
            break;
        }
    }
    if (i == 4) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F3FC7[i * 5]);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
    Game_SetScriptActive();
    event            = D_801F3FC8[i * 5];
    g_SceneEventStep = 0;
    g_SceneEventMode = event;
    return 1;
}
