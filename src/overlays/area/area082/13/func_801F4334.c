#include "area082_13.h"

MATCH void func_801F4334(void) {
    Actor* task;
    u16    x;
    s16    y;

    task         = g_Task;
    task->unk_32 = (task->unk_32 - (task->vz / 10000)) & 0xFFD;

    g_Task->vx = rand() & 0x2000;
    g_Task->vy = rand() & 0x2000;

    if ((g_Task->screen_x & 0x800) != (g_Task->unk_32 & 0x800)) {
        if ((s16)g_Task->screen_y >= 0x41) {
            g_Task->param.facing = ((s16)g_Task->unk_32 >> 11) + 1;
        }
    }

    y                = g_Task->screen_y - 2;
    x                = g_Task->unk_32;
    g_Task->screen_y = y;
    g_Task->screen_x = x;
    if (y == 0) {
        g_ScriptVars[0] += 1;
        func_80196070();
    }
    func_801F4430();
}
