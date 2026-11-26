#include "area172_13.h"

MATCH void func_801F440C(void) {
    Actor* work;

    SELF(Actor)->header.flags &= ~0x40;
    SELF(Actor)->header.flags |= 0x20;
    SELF(Actor)->tint.bytes.flags   = 1;
    SELF(Actor)->tint.steps.delta.r = -0x80;
    SELF(Actor)->tint.steps.delta.g = -0x80;
    SELF(Actor)->tint.steps.delta.b = -0x80;
    work                            = SELF(Actor);
    work->unk_04                    = 1;
    setVector(work, 0, 0, 0);
    work->gravity = -8;
    g_ScriptState->cursor -= 2;
}
