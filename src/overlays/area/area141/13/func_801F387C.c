#include "area141_13.h"

MATCH void func_801F387C(void) {
    Actor* work;

    SELF(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    SELF(Actor)->tint.bytes.flags = 1;
    work                          = SELF(Actor);
    work->tint.steps.delta.b      = -0x80;
    work->tint.steps.delta.g      = -0x80;
    work->tint.steps.delta.r      = -0x80;
    func_801F390C();
    SELF(Actor)->unk_04 = 1;
}
