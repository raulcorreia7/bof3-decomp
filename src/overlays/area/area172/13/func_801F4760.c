#include "area172_13.h"

MATCH void func_801F4760(void) {
    Actor* work;

    SELF(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    SELF(Actor)->tint.steps.flags = 1;
    work                          = SELF(Actor);
    work->tint.steps.delta.b      = -0x80;
    work->tint.steps.delta.g      = -0x80;
    work->tint.steps.delta.r      = -0x80;
    func_801F47F0();
    SELF(Actor)->unk_04 = 1;
}
