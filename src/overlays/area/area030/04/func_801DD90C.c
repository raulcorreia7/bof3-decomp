#include "area030_04.h"

/* When slot 6's mode is clear, increments slot 1's mode,
 * writes 1 to byte 0x02 and 0 to byte 0x03 of the scratchpad work object. */
MATCH void func_801DD90C(void) {
    if (g_SpawnedActors[6].header.mode == 0) {
        g_SpawnedActors[1].header.mode += 1;
        TASK(FishingState)->mode_index = 1;
        TASK(FishingState)->sub_index  = 0;
    }
}
