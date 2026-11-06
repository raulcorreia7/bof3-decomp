#include "area134_13.h"

MATCH void func_801F3C44(void) {
    Actor* row;
    u8*    work;
    s32    i;

    i    = 0;
    work = (u8*)g_Task;
    TASK_SET(&g_Actors[1]);
    row = &g_Actors[1];
    do {
        row->pos.y.fixed += 0x4000;
        i++;
    } while ((u8)i < 2);
    work[1] = 0x12;
    g_Task  = work;
}
