#include "game_00.h"

/* func_8019C344 */
MATCH s32 Area_GetVx(s32 x, s32 y) {
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
    if (func_8019C4F0(xh, yh) & BYTE_MASK) {
        return 1;
    }
    if (g_Task->vx != 0) {
        if ((x & HALF_MASK) == 0) {
            goto fail; /* miss: return 0 */
        }
        pos = (xh << 16) | 0x8000;
        func_80154ABC(pos, y, g_Task->direction_08);
        if (SP_REF(u8, 0x0u) != 0) {
            if (COORD_INT(g_Task->pos.z) < Area_SampleHeight(pos, y)) {
                return 1;
            }
        }
        if (g_Task->vx <= 0) {
            goto fail; /* miss: return 0 */
        }
        next_x = (s16)((x >> 16) + 1);
        next_y = y >> 16;
    } else {
        if ((y & HALF_MASK) == 0) {
            goto fail; /* miss: return 0 */
        }
        pos = (yh << 16) | 0x8000;
        func_80154ABC(x, pos, g_Task->direction_08);
        if (SP_REF(u8, 0x0u) != 0) {
            if (COORD_INT(g_Task->pos.z) < Area_SampleHeight(x, pos)) {
                return 1;
            }
        }
        if (g_Task->vy <= 0) {
            goto fail; /* miss: return 0 */
        }
        next_x = x >> 16;
        next_y = (s16)((y >> 16) + 1);
    }
    if (func_8019C4F0(next_x, next_y) & BYTE_MASK) {
        return 1;
    }
/* Shared zero return for both miss paths. */
fail:
    return 0;
}
