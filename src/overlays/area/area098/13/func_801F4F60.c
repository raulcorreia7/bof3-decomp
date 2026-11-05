#include "area098_13.h"

MATCH void func_801F4F60(Actor* actor) {
    u8 state;

    actor->unk_03 += 0x10;
    state       = actor->step - 1;
    actor->step = state;
    if (state == 0) {
        actor->step = actor->unk_04;
        actor->mode++;
        if (D_801F6510 == 0) {
            D_801F6510 = 1;
        }
    }
}
