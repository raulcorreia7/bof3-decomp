#include "area082_13.h"

MATCH void func_801F4334(void) {
    Actor* task;
    u16    x;
    s16    y;

    task         = TASK(Actor);
    task->unk_32 = (task->unk_32 - (task->vz / 10000)) & 0xFFD;

    TASK(Actor)->vx = rand() & 0x2000;
    TASK(Actor)->vy = rand() & 0x2000;

    if ((TASK(Actor)->screen_x & 0x800) != (TASK(Actor)->unk_32 & 0x800)) {
        if ((s16)TASK(Actor)->screen_y >= 0x41) {
            TASK(Actor)->param.facing = ((s16)TASK(Actor)->unk_32 >> 11) + 1;
        }
    }

    y                     = TASK(Actor)->screen_y - 2;
    x                     = TASK(Actor)->unk_32;
    TASK(Actor)->screen_y = y;
    TASK(Actor)->screen_x = x;
    if (y == 0) {
        g_ScriptVars[0] += 1;
        func_80196070();
    }
    func_801F4430();
}
