#include "area044_13.h"

/* Sets the flag bit of the trigger record that matches the two cell coordinates and queues its cue. */
MATCH s32 func_801F33A8(s32 x, s32 y) {
    s32 i;
    s32 off;
    u8* mode;
    u8  next_mode;

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
    SND_PlaySE(EMI_CUE_ID(SND_BANK_AREA, 0));
    Game_SetScriptActive();
    next_mode              = D_801F3FC8[i * 5];
    g_SceneEventState.step = 0;
    g_SceneEventState.mode = next_mode;
    return 1;
}
