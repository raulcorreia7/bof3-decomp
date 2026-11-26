#include "engine/slus/slus.h"

/* integrates the positive velocity components at +0xC/+0x10 into
 * the work record's +0x34/+0x38 coordinates, then clears the low 15 bits of
 * each coordinate, snapping both to 0x8000 units.
 */
MATCH void Actor_ApplyVelocity(void) {
    s32 value;

    value = SELF(Actor)->vx;
    if (value > 0) {
        SELF(Actor)->pos.x.fixed += value;
    }
    SELF(Actor)->pos.x.fixed &= -0x8000;
    value = SELF(Actor)->vy;
    if (value > 0) {
        SELF(Actor)->pos.y.fixed += value;
    }
    SELF(Actor)->pos.y.fixed &= -0x8000;
}
