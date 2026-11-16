#include "area111_13.h"

MATCH void func_801F4510(s32 direction) {
    u8 row;
    u8 column;
    u8 selection;

    row    = (g_Game.members[0].pos.y.part.integer - 177) / 2;
    column = (g_Game.members[0].pos.x.part.integer - 11) / 2;

    if ((column & 1) != 0) {
        selection = D_801F5C18[row][column >> 1] & 0xF;
    } else {
        selection = D_801F5C18[row][column >> 1] >> 4;
    }

    selection -= 1;
    g_SceneEventSelection              = selection;
    g_SceneEventMode                   = 0x11;
    g_SceneEventStep                   = direction;
    D_80147A58[selection].direction_08 = direction;
    Game_SetScriptActive();
}
