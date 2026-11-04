#include "engine/slus/slus.h"

/* subtracts amount from the g_Zenny counter when it is large enough,
 * reporting success. unused is unused; every caller passes 0.
 */
MATCH s32 Party_SpendZenny(u32 amount, s32 unused) {
    u32  value;
    s32  result;
    u32* zenny;

    zenny = &g_Zenny;

    value = zenny[0];
    if (value >= amount) {
        result   = value - amount;
        zenny[0] = result;
        return 1;
    }
    return 0;
}
