#include "area086_13.h"
#include "area/spad.h"

MATCH void func_801F2D28(void) {
    Actor* task;
    s8     delta;

    task        = g_Task;
    delta       = D_801F3670[COORD_INT(task->pos.y)];
    task->timer = task->timer + 1;
    COORD_INT(task->pos.z) += delta;
    if (g_Task->timer >= 0x10) {
        COORD_INT(g_Task->pos.y) = (COORD_INT(g_Task->pos.y) + 1) & 3;
        /* FAKE: retail passes the full halfword; the shared SYS_ClearFlag prototype (u8) lacks it. */
        ((void (*)(void*, s32))SYS_ClearFlag)(g_SceneEventFlags, COORD_FRAC(g_Task->pos.x));
        g_Task->header.step -= 1;
    }
    func_801F2DE8();
    func_801F3070();
}
