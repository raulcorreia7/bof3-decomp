#include "game_00.h"

MATCH void func_801B8A9C(void) {
    s16 vals[2];
    u8  route;
    /* FAKE: retail keeps the direction counter in s2. */
    MATCH_REG(s32, count, "s2");
    /* FAKE: retail keeps the step count in v1. */
    MATCH_REG(s32, steps, "v1");
    s32 word;
    s32 offset;
    /* FAKE: retail keeps the work-area pointer in a1. */
    MATCH_REG(Actor*, work, "a1");
    s32        pos_x;
    s32        pos_y;
    u8         index_copy;
    const s32* px;
    s32*       py;
    s32        found;
    s32        iter;

    count = 0;
loop_top:
    work   = g_SpadWork;
    route  = count;
    route  = (work->direction_08 + route) & 7;
    word   = VOL(u32, FIELD(u32, work, 0x70u));
    offset = route * 2;
    pos_x  = work->x.fixed + g_FacingSteps[route].x * (steps = (word & BYTE_MASK) + 1);
    pos_y  = work->y.fixed + D_80181B98[offset] * steps;
    if ((func_801C3E40(pos_x, pos_y, (u8)word, g_SpadWork->z.part.integer) & BYTE_MASK) != 0u ||
        (func_801C472C(pos_x, pos_y, g_SpadWork->state_70.byte, 0xD0, 0) & BYTE_MASK) == 0u) {
        count++;
        if (count < 8) {
            /* Retry the probe from the next direction. */
            goto loop_top;
        }
        found   = 1;
        route   = g_SpadWork->direction_08;
        vals[0] = g_SpadWork->z.part.integer;
        for (iter = 0; iter < 4; iter++) {
            index_copy = iter * 2 + 1;
            px         = &g_FacingSteps[(index_copy & BYTE_MASK)].x;
            py         = &D_80181B98[(index_copy & BYTE_MASK) * 2];
            if ((func_801B8C64(g_SpadWork->x.fixed + *px, g_SpadWork->y.fixed + *py, &vals[found], 1) & BYTE_MASK) !=
                0u) {
                found++;
            }
            if (found == 2) {
                /* FAKE: do-while(0) scope steers regalloc */
                do {
                    found = 1;
                    if (vals[1] < vals[0]) {
                        vals[0] = vals[1];
                        route   = index_copy;
                    }
                } while (0);
            }
        }
    }
    g_SpadWork->direction_08 = route;
}
