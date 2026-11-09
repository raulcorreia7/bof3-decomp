#include "area148_13.h"

MATCH u8 func_801F41A0(u8 x, u8 y) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (x == D_801F615C[i].x && y == D_801F615C[i].y && (D_801F615C[i].facing & 0xF) == g_Game.members[0].facing) {
            break;
        }
    }
    if (i == 1) {
        return 0;
    }
    Game_SetScriptActive();
    g_SceneEventMode = 0x1F;
    g_SceneEventStep = D_801F615C[i].step;
    return 1;
}
