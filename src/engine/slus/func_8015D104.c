#include "engine/slus/slus.h"

/* subtracts amount from the indexed D_80148FF8 byte, clamping it at zero.
 */
MATCH void func_8015D104(s32 slot, s32 amount) {
    u32 index;
    s8  value;

    index             = slot & HALF_MASK;
    value             = D_80148FF8[index] - amount;
    D_80148FF8[index] = value;
    if (value <= 0) {
        D_80148FF8[index] = 0;
    }
}
