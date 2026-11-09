#include "engine/slus/slus.h"

/* adds amount to the indexed D_80148FE0 byte, resetting it at 0x7F. */
MATCH void func_8015D0B8(s32 slot, s32 amount) {
    u32 index;
    s8  value;

    index             = slot & HALF_MASK;
    value             = D_80148FE0[index] + amount;
    D_80148FE0[index] = value;
    if (value >= 0x7F) {
        D_80148FE0[index] = 0;
    }
}
