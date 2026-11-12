#include "area052_13.h"

MATCH bool func_801F3D44(void) {
    u8  i;
    s32 rect_index;

    rect_index = g_SceneEventStep != 0;
    for (i = 0; i < g_Game.party_size; i++) {
        if ((u16)(COORD_INT(g_Game.members[i].pos.x) - D_801F510C[rect_index].x) < D_801F510C[rect_index].width) {
            if ((u16)(COORD_INT(g_Game.members[i].pos.y) - D_801F510C[rect_index].y) < D_801F510C[rect_index].height) {
                return true;
            }
        }
    }
    return false;
}
