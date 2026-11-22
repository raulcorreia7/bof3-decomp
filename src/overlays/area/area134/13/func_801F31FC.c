#include "area134_13.h"

MATCH void func_801F31FC(void) {
    Actor* actor;
    u8*    work;
    s32    i;

    i    = 0;
    work = TASK(u8);
    TASK_SET(&g_Actors[0]);
    actor = &g_Actors[0];
    do {
        actor->pos.y.fixed += 0x4000;
        i++;
    } while ((u8)i < 2);
    work[1] = 0xE;
    g_Task  = work;
    work[9] = 8;
}
