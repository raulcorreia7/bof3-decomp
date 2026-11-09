#include "area135_14.h"

MATCH u8 func_801F5130(u8 x, u8 y) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (x == D_801F6BA8[i].x && y == D_801F6BA8[i].y && (D_801F6BA8[i].facing & 0xF) == g_Game.members[0].facing) {
            break;
        }
    }
    if (i == 2) {
        return 0;
    }
    Game_SetScriptActive();
    g_SceneEventMode = 0x12;
    g_SceneEventStep = D_801F6BA8[i].step;
    return 1;
}
