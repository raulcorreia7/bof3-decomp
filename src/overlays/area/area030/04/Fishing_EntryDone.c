#include "area030_04.h"

/* When byte `D_80144199` equals 4, increments byte `D_8014403D`,
 * then advances the scratchpad work object: byte 0x02 += 1, byte 0x03 = 0. */
/* func_801D9C9C */
MATCH void Fishing_EntryDone(void) {
    if (D_80144199 == 4) {
        D_8014403D += 1;
        FISHING_STATE->mode_index_02 += 1;
        FISHING_STATE->sub_index_03 = 0;
    }
}
