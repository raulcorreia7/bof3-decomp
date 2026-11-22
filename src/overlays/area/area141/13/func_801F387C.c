#include "area141_13.h"

MATCH void func_801F387C(void) {
    Actor* work;

    TASK(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    TASK(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    TASK(Actor)->tint.bytes.flags = 1;
    work                          = TASK(Actor);
    work->tint.steps.delta.b      = -0x80;
    work->tint.steps.delta.g      = -0x80;
    work->tint.steps.delta.r      = -0x80;
    func_801F390C();
    TASK(Actor)->unk_04 = 1;
}
