#include "area134_13.h"

MATCH void func_801F2F3C(void) {
    Actor* row;
    u8*    work;
    s32    i;

    i    = 0;
    work = (u8*)g_Task;
    TASK_SET(&g_Actors[0]);
    row = &g_Actors[0];
    do {
        row->pos.x.fixed += 0x4000;
        i++;
    } while ((u8)i < 4);
    work[1] = 7;
    g_Task  = work;
}
