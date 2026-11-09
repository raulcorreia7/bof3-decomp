#include "area030_04.h"

/* Sums the per-slot results of the slot helper for every set byte of
 * the 32-entry table and returns the 16-bit total. */
/* func_801E0B6C */
MATCH s32 Fishing_TotalScore(void) {
    s32 i;
    s32 total;

    total = 0;
    for (i = 0; i < 32; i++) {
        if (g_FishingBestCatch[i] != 0) {
            total += Fishing_CatchScore(i, g_FishingBestCatch[i]);
        }
    }
    return total & HALF_MASK;
}
