#include "area030_04.h"

/* Sums the per-slot results of the slot helper for every set byte of
 * the 32-entry table and returns the 16-bit total. */
MATCH s32 func_801E0B6C(void) {
    s32 i;
    s32 total;

    total = 0;
    for (i = 0; i < 32; i++) {
        if (g_SaveData.fish_best_catch[i] != 0) {
            total += func_801E0ABC(i, g_SaveData.fish_best_catch[i]);
        }
    }
    return total & HALF_MASK;
}
