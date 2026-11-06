#include "engine/slus/slus.h"

/* integrates the positive velocity components at +0xC/+0x10 into
 * the work record's +0x34/+0x38 coordinates, then clears the low 15 bits of
 * each coordinate, snapping both to 0x8000 units.
 */
MATCH void Actor_ApplyVelocity(void) {
    s32 value;

    value = g_Task->vx;
    if (value > 0) {
        g_Task->pos.x.fixed += value;
    }
    g_Task->pos.x.fixed &= -0x8000;
    value = g_Task->vy;
    if (value > 0) {
        g_Task->pos.y.fixed += value;
    }
    g_Task->pos.y.fixed &= -0x8000;
}
