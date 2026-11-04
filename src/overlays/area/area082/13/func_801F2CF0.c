#include "area082_13.h"

MATCH void func_801F2CF0(void) {
    u16    timer;
    Actor* actor;

    actor         = g_SpadWork;
    timer         = actor->unk_2C - 1;
    actor->unk_2C = timer;
    if (!(timer & HALF_MASK)) {
        actor->unk_2C = 12;
        actor->unk_01 = actor->unk_01 + 1;
    }
}
