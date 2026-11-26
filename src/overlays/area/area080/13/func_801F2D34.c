#include "area080_13.h"

MATCH void func_801F2D34(void) {
    u8 remaining;

    D_801F44A0->unk_23 += 3;
    Area_ProjectRing(D_801F44A0);
    func_801F31A0(D_801F44A0);
    ACTOR_COUNT_DOWN(SELF(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        func_801F3834();
        SELF(Actor)->timer = 120;
        SELF(Actor)->header.mode++;
    }
}
