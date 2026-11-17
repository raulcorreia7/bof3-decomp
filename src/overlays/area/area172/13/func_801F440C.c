#include "area172_13.h"

MATCH void func_801F440C(void) {
    Actor* work;

    g_Task->header.flags &= ~0x40;
    g_Task->header.flags |= 0x20;
    g_Task->tint.bytes.flags   = 1;
    g_Task->tint.steps.delta.r = -0x80;
    g_Task->tint.steps.delta.g = -0x80;
    g_Task->tint.steps.delta.b = -0x80;
    work                       = g_Task;
    work->unk_04               = 1;
    setVector(work, 0, 0, 0);
    work->gravity = -8;
    g_ScriptState->cursor -= 2;
}
