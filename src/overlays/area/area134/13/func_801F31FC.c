#include "area134_13.h"

MATCH void func_801F31FC(void) {
    Actor* row;
    u8*    work;
    s32    i;

    i    = 0;
    work = (u8*)g_Task;
    TASK_SET(&g_Actors[0]);
    row = &g_Actors[0];
    do {
        row->y.fixed += 0x4000;
        i++;
    } while ((u8)i < 2);
    work[1] = 0xE;
    g_Task  = work;
    work[9] = 8;
}
