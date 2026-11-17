#include "area141_13.h"

MATCH void func_801F387C(void) {
    Actor* work;

    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->tint.bytes.flags = 1;
    work                     = g_Task;
    work->tint.steps.delta.b = -0x80;
    work->tint.steps.delta.g = -0x80;
    work->tint.steps.delta.r = -0x80;
    func_801F390C();
    g_Task->unk_04 = 1;
}
