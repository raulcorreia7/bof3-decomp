#include "area134_13.h"

MATCH void func_801F331C(void) {
    Actor* row;
    u8*    work;
    s32    i;

    i      = 0;
    work   = (u8*)g_Task;
    g_Task = (u8*)&g_Actors[0];
    row    = &g_Actors[0];
    do {
        row->y.fixed += 0x4000;
        i++;
    } while ((u8)i < 2);
    work[1] = 0x12;
    g_Task  = work;
}
