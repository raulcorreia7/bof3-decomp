#include "game_00.h"

MATCH void func_801B8A9C(void) {
    s16 vals[2];
    u8  route;
    /* FAKE: retail keeps the direction counter in s2. */
    FAKE_REG(s32, count, "s2");
    /* FAKE: retail keeps the step count in v1. */
    FAKE_REG(s32, steps, "v1");
    s32 word;
    s32 offset;
    /* FAKE: retail keeps the work-area pointer in a1. */
    FAKE_REG(Actor*, work, "a1");
    s32        pos_x;
    s32        pos_y;
    u8         index_copy;
    const s32* px;
    s32*       py;
    s32        found;
    s32        iter;

    count = 0;
loop_top:
    work   = g_Task;
    route  = count;
    route  = (work->direction_08 + route) & 0x7;
    word   = VOL(u32, FIELD(u32, work, 0x70u));
    offset = route * 2;
    pos_x  = work->pos.x.fixed + g_FacingSteps[route].x * (steps = (word & BYTE_MASK) + 1);
    pos_y  = work->pos.y.fixed + g_FacingStepY[offset] * steps;
    if ((func_801C3E40(pos_x, pos_y, (u8)word, COORD_INT(g_Task->pos.z)) & BYTE_MASK) != 0u || (func_801C472C(pos_x, pos_y, g_Task->state_70.byte, 0xD0, 0) & BYTE_MASK) == 0u) {
        count++;
        if (count < 8) {
            /* Retry the probe from the next direction. */
            goto loop_top;
        }
        found   = 1;
        route   = g_Task->direction_08;
        vals[0] = COORD_INT(g_Task->pos.z);
        for (iter = 0; iter < 4; iter++) {
            index_copy = iter * 2 + 1;
            px         = &g_FacingSteps[(index_copy & BYTE_MASK)].x;
            py         = &g_FacingStepY[(index_copy & BYTE_MASK) * 2];
            if ((func_801B8C64(g_Task->pos.x.fixed + *px, g_Task->pos.y.fixed + *py, &vals[found], 1) & BYTE_MASK) != 0u) {
                found++;
            }
            if (found == 2) {
                /* FAKE: the order lock steers regalloc */
                FAKE_ORDER_LOCK_BEGIN
                    found = 1;
                    if (vals[1] < vals[0]) {
                        vals[0] = vals[1];
                        route   = index_copy;
                    }
                FAKE_ORDER_LOCK_END;
            }
        }
    }
    g_Task->direction_08 = route;
}
