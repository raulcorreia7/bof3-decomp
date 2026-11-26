#include "engine/game/00/game_00.h"

/* func_8019C344 */
/* Returns whether the point blocks the rock: its own cell, the half cell it enters and any ground above the rock. */
MATCH s32 Actor_RockIsPointBlocked(s32 x, s32 y) {
    /* FAKE: retail homes the x high half in $s4. */
    FAKE_REG(s32, xh, "s4");
    /* FAKE: retail homes the y high half in $s1. */
    FAKE_REG(s32, yh, "s1");
    /* FAKE: retail homes the packed probe position in $s0. */
    FAKE_REG(s32, pos, "s0");
    /* FAKE: retail homes the x probe argument in $a0. */
    FAKE_REG(s32, next_x, "a0");
    /* FAKE: retail homes the y probe argument in $a1. */
    FAKE_REG(s32, next_y, "a1");

    xh = x >> 16;
    yh = y >> 16;
    if (Actor_RockIsCellBlocked(xh, yh) & BYTE_MASK) {
        return 1;
    }
    if (TASK(Actor)->vx != 0) {
        if ((x & HALF_MASK) == 0) {
            goto fail;
        }
        pos = (xh << 16) | 0x8000;
        Area_HeightGet(pos, y, TASK(Actor)->direction);
        if (SP_REF(u8, 0x0u) != 0) {
            if (COORD_INT(TASK(Actor)->pos.z) < Area_HeightSample(pos, y)) {
                return 1;
            }
        }
        if (TASK(Actor)->vx <= 0) {
            goto fail;
        }
        next_x = (s16)((x >> 16) + 1);
        next_y = y >> 16;
    } else {
        if ((y & HALF_MASK) == 0) {
            goto fail;
        }
        pos = (yh << 16) | 0x8000;
        Area_HeightGet(x, pos, TASK(Actor)->direction);
        if (SP_REF(u8, 0x0u) != 0) {
            if (COORD_INT(TASK(Actor)->pos.z) < Area_HeightSample(x, pos)) {
                return 1;
            }
        }
        if (TASK(Actor)->vy <= 0) {
            goto fail;
        }
        next_x = x >> 16;
        next_y = (s16)((y >> 16) + 1);
    }
    if (Actor_RockIsCellBlocked(next_x, next_y) & BYTE_MASK) {
        return 1;
    }
fail:
    return 0;
}
