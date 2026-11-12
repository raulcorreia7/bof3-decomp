#include "area030_04.h"

/* Reports whether the area030 anchor may settle: graphics mode 4 with
 * an exhausted sprite bank, no pending flag and area state 3, then the
 * scratchpad probe record within 0x7FFF of the anchor on x and y and within
 * 0x400 on z. */
MATCH s32 func_801E0770(void) {
    FishingState* work;
    s32           d;
    s32           dz;
    /* FAKE: retail keeps the y anchor in $a0. */
    FAKE_REG(s32, anchor, "a0");
    s32 limit;
    /* FAKE: retail holds the failure status in $v0 across the guard chain. */
    FAKE_REG(s32, result, "v0");

    result = 0;
    if (4 != g_ActorSlots[0].header.mode) {
        return result;
    }
    if (0xFF != g_FishingHookedFish) {
        return result;
    }
    if (0 != D_80144199) {
        return result;
    }
    limit = 32767;
    if (3 != D_80145E92[0]) {
        return result;
    }
    work = FISHING_STATE;
    d    = -g_ActorSlots[0].pos.x.fixed + work->motion_34.unk_34;
    if (d < 0) {
        d = -d;
    }
    if (d > 0x7FFF) {
        return result;
    }
    d      = work->y_38.pos_y;
    anchor = g_ActorSlots[0].pos.y.fixed;
    d      = d - anchor;
    d      = ABS(d);
    if (d > limit) {
        return result;
    }
    dz = work->bounce_3C.half.key_3E;
    dz = dz - COORD_INT(g_ActorSlots[0].pos.z);
    dz = ABS(dz);
    return dz < 0x400;
}
