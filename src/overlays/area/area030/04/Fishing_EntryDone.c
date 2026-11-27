#include "area030_04.h"

/* When byte `D_80144199` equals 4, increments byte `D_8014403D`,
 * then advances the scratchpad work object: byte 0x02 += 1, byte 0x03 = 0. */
/* func_801D9C9C */
MATCH void Fishing_EntryDone(void) {
    if (g_SpawnedActors[4].header.mode == 4) {
        g_SpawnedActors[1].header.mode += 1;
        SELF(FishingState)->mode_index += 1;
        SELF(FishingState)->sub_index = 0;
    }
}
