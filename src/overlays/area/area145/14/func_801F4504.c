#include "area145_14.h"

MATCH u8 func_801F4504(u8 x, u8 y) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (x == D_801F5CC0[i].x && y == D_801F5CC0[i].y && (D_801F5CC0[i].facing & 0xF) == g_Game.members[0].facing) {
            break;
        }
    }
    if (i == 7) {
        return 0;
    }
    if (SYS_TestFlag(D_80144EF0, 9)) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x14;
        g_SceneEventStep = D_801F5CC0[i].step;
        return 1;
    }
    return 0;
}
