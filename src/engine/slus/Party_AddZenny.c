#include "engine/slus/slus.h"

/* adds amount to the g_Zenny accumulator (and to D_80145030 when skip_earned is
 * zero), clamping the accumulator at 0x98967F.
 */
MATCH s32 Party_AddZenny(s32 amount, s32 skip_earned) {
    u32  sum;
    u32* zenny;

    zenny = &g_Zenny;

    sum      = zenny[0] + amount;
    zenny[0] = sum;
    if ((skip_earned & BYTE_MASK) == 0) {
        D_80145030 = D_80145030 + amount;
    }
    if (0x98967Fu < sum) {
        zenny[0] = 0x98967F;
        return 0;
    }
    return 1;
}
