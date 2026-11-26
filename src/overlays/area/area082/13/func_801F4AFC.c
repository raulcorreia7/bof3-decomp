#include "area082_13.h"

MATCH void func_801F4AFC(void) {
    Actor* actor;

    func_801F5388(0x80);
    actor              = SELF(Actor);
    D_8014933A         = 1;
    actor->header.step = actor->header.step + 1;
}
