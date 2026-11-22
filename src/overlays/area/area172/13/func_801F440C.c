#include "area172_13.h"

MATCH void func_801F440C(void) {
    Actor* work;

    TASK(Actor)->header.flags &= ~0x40;
    TASK(Actor)->header.flags |= 0x20;
    TASK(Actor)->tint.bytes.flags   = 1;
    TASK(Actor)->tint.steps.delta.r = -0x80;
    TASK(Actor)->tint.steps.delta.g = -0x80;
    TASK(Actor)->tint.steps.delta.b = -0x80;
    work                            = TASK(Actor);
    work->unk_04                    = 1;
    setVector(work, 0, 0, 0);
    work->gravity = -8;
    g_ScriptState->cursor -= 2;
}
