#include "engine/slus/slus.h"

/* integrates the positive velocity components at +0xC/+0x10 into the record's +0x34/+0x38 coordinates. */
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
