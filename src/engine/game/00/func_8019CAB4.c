#include "game_00.h"

MATCH u8 func_8019CAB4(void) {
    Actor* work;
    s8     id;
    u8     walkable;

    work = g_Task;
    id   = func_801BDE14(work->x.fixed, work->y.fixed, 0);
    if (id != -1) {
        g_Actors[id].flags_74 |= ACTOR_FLAG_INTERACTION_PENDING;
        return 1;
    }
    if (D_80145ECE + 64 < Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed)) {
        walkable = 1;
    } else {
        work     = g_Task;
        walkable = (Area_GetCellCode(work->x.part.integer, work->y.part.integer) & BYTE_MASK) == 0x11;
    }
    return walkable;
}
