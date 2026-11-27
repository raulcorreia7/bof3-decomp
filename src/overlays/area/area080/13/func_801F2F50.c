#include "area080_13.h"

MATCH void func_801F2F50(void) {
    u8 remaining;

    setVector(&D_801F44A0->center, D_80146954.x.fixed, D_80146954.y.fixed, D_80146954.z.fixed);
    Area_ProjectRing(D_801F44A0);
    func_801F31A0(D_801F44A0);
    func_801F33DC(D_801F44A0);
    func_801F3870();
    ACTOR_COUNT_DOWN(SELF(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        SELF(Actor)->timer = AREA_RING_STEP_FRAMES;
        SELF(Actor)->header.mode += 1;
    }
}
