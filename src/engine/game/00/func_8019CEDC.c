#include "game_00.h"

MATCH void func_8019CEDC(void) {
    Actor* work;
    s32    moved;

    g_Task->timer = (g_Task->timer - 1);
    work          = g_Task;
    work->pos.x.fixed += work->vx;
    moved             = work->pos.y.fixed + work->vy;
    work->pos.y.fixed = moved;
    if (work->timer == 0) {
        if (LOHU(g_GameAreaId) == AREA_ID_ANGEL_TOWER_LOWER) {
            if ((work->pos.x.fixed == TO_COORD(17) + COORD_HALF) && (moved == TO_COORD(74) + COORD_HALF)) {
                SYS_SetFlag(g_SceneEventFlags, 54);
            } else {
                SYS_ClearFlag(g_SceneEventFlags, 54);
            }
        }
        func_8019D270();
        g_Task->param.unk_0B = 0;
        g_Task->header.mode  = 1;
    }
    func_8015A944();
}
