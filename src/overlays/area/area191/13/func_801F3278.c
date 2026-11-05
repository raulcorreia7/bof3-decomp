/* Every step re-reads the scratchpad cell. */
#define SPAD_WORK_VOLATILE
#include "area191_13.h"

MATCH void func_801F3278(void) {
    /* FAKE: retail keeps the work pointer in v1. */
    MATCH_REG(Actor*, scratch, "v1");
    Actor* check;
    u8     mode;
    s32    x;
    s32    step;
    s32    angle;
    s32    spin;

    scratch          = g_SpadWork;
    mode             = scratch->unk_0A - 1;
    x                = scratch->x.fixed;
    step             = scratch->unk_0C;
    angle            = scratch->unk_40;
    scratch->x.fixed = x + step;
    spin             = scratch->unk_44;
    scratch->unk_40  = angle + 0x2000;
    scratch->unk_0A  = mode;
    check            = g_SpadWork;
    scratch->unk_44  = spin + 0x2000;

    if ((check->unk_0A & 3) == 0) {
        check->unk_04 = 2;
    }

    scratch = g_SpadWork;
    if (scratch->unk_0A == 0) {
        scratch->unk_04 = 0;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
