#include "area191_13.h"

MATCH void func_801F3278(void) {
    Actor* scratch;
    Actor* work;
    Actor* check;
    u8     mode;
    s32    x;
    s32    step;
    s32    angle;
    s32    spin;

    scratch              = g_Task;
    mode                 = scratch->unk_0A - 1;
    x                    = scratch->pos.x.fixed;
    step                 = scratch->vx;
    angle                = scratch->scale.x;
    scratch->pos.x.fixed = x + step;
    spin                 = scratch->scale.y;
    scratch->scale.x     = angle + 0x2000;
    scratch->unk_0A      = mode;
    check                = g_Task;
    scratch->scale.y     = spin + 0x2000;

    if ((check->unk_0A & 0x3) == 0) {
        check->unk_04 = 2;
    }

    /* FAKE: retail splits the last re-read across the copy so the row stays
     * in one register. */
    work    = g_Task;
    scratch = work;
    if (scratch->unk_0A == 0) {
        work->unk_04 = 0;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
