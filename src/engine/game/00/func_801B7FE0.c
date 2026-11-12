#include "game_00.h"

MATCH void func_801B7FE0(void) {
    Actor* work;
    Actor* store;
    s16    value;
    u8     arg;

    work = g_Task;
    COORD_INT(work->pos.z) -= 16;
    if ((s16)COORD_INT(work->pos.z) < Area_ReadHeight(work->pos.x.fixed, work->pos.y.fixed)) {
        value                   = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
        store                   = g_Task;
        store->timer            = 2;
        COORD_INT(store->pos.z) = value;
        g_Task->unk_0A          = 0;
        Actor_RequestScript((g_Task->direction_08 == FACING_RIGHT) ? 7 : 1);
        g_Task->unk_04 = 9;
    }
    Actor_StepAnimLoop();
}
