#include "area080_13.h"

MATCH void func_801F2E7C(void) {
    s16 radius;
    u8  timer;

    radius             = D_801F44A0->radius + 0x30;
    D_801F44A0->radius = radius;
    if (radius > 384) {
        D_801F44A0->radius = 384;
    }
    Area_ProjectRing(D_801F44A0);
    func_801F31A0((s32)D_801F44A0);
    func_801F33DC(D_801F44A0);
    func_801F3870();
    ACTOR_COUNT_DOWN(SELF(Actor), timer, timer);
    if ((timer & BYTE_MASK) == 0) {
        SELF(Actor)->timer = 120;
        SELF(Actor)->header.mode++;
    }
}
