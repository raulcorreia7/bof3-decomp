#include "area111_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4510(s32 step) {
    u8 x;
    u8 y;
    u8 value;
    u8 selection;

    x = (g_Game.members[0].pos.x.part.integer - 11) / 2;
    y = (g_Game.members[0].pos.y.part.integer - 177) / 2;
    if (x & 1) {
        value = D_801F5C18[y][x / 2] & 0xF;
    } else {
        value = D_801F5C18[y][x / 2] >> 4;
    }
    selection                          = value - 1;
    g_SceneEventSelection              = selection;
    g_SceneEventMode                   = 0x11;
    g_SceneEventStep                   = step;
    D_80147A58[selection].direction_08 = step;
    Game_SetScriptActive();
}
#else
INCLUDE_ASM(func_801F4510);
#endif
