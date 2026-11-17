#include "area141_13.h"

MATCH void func_801F3740(void) {
    s8     tuneA;
    s8     tuneB;
    s8     tuneC;
    Actor* spad;
    Actor* spad2;

    spad = g_Task;
    spad->pos.x.fixed += spad->vx;
    spad->pos.y.fixed += spad->vy;
    tuneA = spad->tint.steps.delta.r;
    if (tuneA != -0x80) {
        spad->tint.steps.delta.r = (tuneA - 2);
    }
    spad2 = g_Task;
    tuneB = spad2->tint.steps.delta.g;
    if (tuneB != -0x80) {
        spad2->tint.steps.delta.g = (tuneB - 2);
        spad2                     = g_Task;
    }
    tuneC = spad2->tint.steps.delta.b;
    if (tuneC != -0x80) {
        spad2->tint.steps.delta.b = (tuneC - 2);
    }
    if ((g_Task->tint.raw & ~0xFF) == 0x80808000) {
        g_Task->header.flags |= 0x40;
        g_Task->unk_04 = 0;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
