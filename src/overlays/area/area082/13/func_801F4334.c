#include "area082_13.h"

MATCH void func_801F4334(void) {
    Actor* task;
    u16    x;
    s16    y;

    task         = SELF(Actor);
    task->unk_32 = (task->unk_32 - (task->vz / 10000)) & 0xFFD;

    SELF(Actor)->vx = rand() & 0x2000;
    SELF(Actor)->vy = rand() & 0x2000;

    if ((SELF(Actor)->screen_x & 0x800) != (SELF(Actor)->unk_32 & 0x800)) {
        if (SELF(Actor)->screen_y >= 0x41) {
            SELF(Actor)->param.facing = ((s16)SELF(Actor)->unk_32 >> 11) + 1;
        }
    }

    y                     = SELF(Actor)->screen_y - 2;
    x                     = SELF(Actor)->unk_32;
    SELF(Actor)->screen_y = y;
    SELF(Actor)->screen_x = x;
    if (y == 0) {
        g_ScriptVars[0] += 1;
        func_80196070();
    }
    func_801F4430();
}
