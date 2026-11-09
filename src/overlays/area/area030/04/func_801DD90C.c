#include "area030_04.h"

/* When flag `D_80144281` is clear, increments byte `D_8014403D`,
 * writes 1 to byte 0x02 and 0 to byte 0x03 of the scratchpad work object. */
MATCH void func_801DD90C(void) {
    if (D_80144281 == 0) {
        D_8014403D += 1;
        FISHING_STATE->mode_index_02 = 1;
        FISHING_STATE->sub_index_03  = 0;
    }
}
