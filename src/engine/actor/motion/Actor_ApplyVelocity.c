#include "engine/slus/slus.h"

/* integrates the positive velocity components at +0xC/+0x10 into
 * the work record's +0x34/+0x38 coordinates, then clears the low 15 bits of
 * each coordinate, snapping both to 0x8000 units.
 */
MATCH void Actor_ApplyVelocity(void) {
    s32 value;

    value = TASK(Actor)->vx;
    if (value > 0) {
        TASK(Actor)->pos.x.fixed += value;
    }
    TASK(Actor)->pos.x.fixed &= -0x8000;
    value = TASK(Actor)->vy;
    if (value > 0) {
        TASK(Actor)->pos.y.fixed += value;
    }
    TASK(Actor)->pos.y.fixed &= -0x8000;
}
