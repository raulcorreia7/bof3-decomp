#include "area082_13.h"

MATCH void func_801F4190(void) {
    Actor* work;
    Actor* band;
    Actor* actor;
    s32    value;
    s32    quotient;
    s32    roll;

    work     = TASK(Actor);
    value    = work->vz;
    quotient = value / 10000;
    value += quotient * (quotient - 10);
    work->unk_32 = (work->unk_32 - work->vz / 10000) & 0xFFD;
    work->vz     = value;
    if ((work->screen_x & 0x800) != (work->unk_32 & 0x800)) {
        work->param.unk_0B = ((s16)work->unk_32 >> 11) + 1;
    }
    band           = TASK(Actor);
    band->screen_x = band->unk_32;
    if ((u32)(band->vz - 680000) <= 340000u) {
        roll            = rand();
        TASK(Actor)->vx = roll & 0x1000;
        roll            = rand();
        TASK(Actor)->vy = roll & 0x1000;
    }
    if (TASK(Actor)->vz > 1019999) {
        roll            = rand();
        TASK(Actor)->vx = roll & 0x2000;
        roll            = rand();
        TASK(Actor)->vy = roll & 0x2000;
        if (g_ScriptVars[0] == 6) {
            g_ScriptVars[0]++;
        }
    }
    actor = TASK(Actor);
    if (actor->vz > 1369999) {
        actor->header.step++;
    }
    func_801F4430();
}
