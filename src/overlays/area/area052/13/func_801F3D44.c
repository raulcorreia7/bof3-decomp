#include "area052_13.h"

MATCH s32 func_801F3D44(void) {
    u8  i;
    s32 row;

    row = g_SceneEventStep != 0;
    for (i = 0; i < g_Game.party_size; i++) {
        if ((u16)(COORD_INT(g_Game.members[i].pos.x) - D_801F510C[row].x) < D_801F510C[row].width) {
            if ((u16)(COORD_INT(g_Game.members[i].pos.y) - D_801F510C[row].y) < D_801F510C[row].height) {
                return 1;
            }
        }
    }
    return 0;
}
