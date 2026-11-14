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
    tuneA = spad->tint.signed_bytes.delta.red;
    if (tuneA != -0x80) {
        spad->tint.signed_bytes.delta.red = (tuneA - 2);
    }
    spad2 = g_Task;
    tuneB = spad2->tint.signed_bytes.delta.green;
    if (tuneB != -0x80) {
        spad2->tint.signed_bytes.delta.green = (tuneB - 2);
        spad2                                = g_Task;
    }
    tuneC = spad2->tint.signed_bytes.delta.blue;
    if (tuneC != -0x80) {
        spad2->tint.signed_bytes.delta.blue = (tuneC - 2);
    }
    if ((g_Task->tint.word & ~0xFF) == 0x80808000) {
        g_Task->header.flags |= 0x40;
        g_Task->unk_04 = 0;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
