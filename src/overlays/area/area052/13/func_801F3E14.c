#include "area052_13.h"

MATCH u8 func_801F3E14(u8 x, u8 y) {
    s32 i;
    /* FAKE: retail addresses the scene flags (g_SceneEventFlags) from the mode byte. */
    u8* mode;

    for (i = 0; i < 4; i++) {
        if (x == D_801F5114[i].x && y == D_801F5114[i].y && (D_801F5114[i].facing & 0xF) == g_Game.members[0].facing) {
            break;
        }
    }
    if (i == 4) {
        return 0;
    }
    Game_SetScriptActive();
    mode             = &g_SceneEventMode;
    *mode            = 15;
    g_SceneEventStep = D_801F5114[i].step;
    if (func_801F3D44() & BYTE_MASK) {
        g_SceneEventStep = 10;
    } else {
        SYS_ToggleFlag(mode + 0x63D, D_801F5114[i].flag);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
    }
    return 1;
}
