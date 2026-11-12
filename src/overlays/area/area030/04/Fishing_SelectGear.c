#include "area030_04.h"

/* Points the two character record cursors at the selected table rows
 * (20-byte and 10-byte strides) when their selector bytes are set. */
/* func_801DDE2C */
MATCH void Fishing_SelectGear(void) {
    if (g_FishingLure != 0) {
        g_FishingLureRow = (FishingTarget*)(D_801E2720 + g_FishingLure * sizeof(FishingTarget));
    }
    if (g_FishingRod != 0) {
        g_FishingRodRow = (FishingRod*)(D_801E2748 + g_FishingRod * sizeof(FishingRod));
    }
}
