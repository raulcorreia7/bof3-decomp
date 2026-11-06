#include "area030_04.h"

/* Counts table entries whose id is in [0x38, 0x4D] and whose flag
 * byte is 0x63, and reports whether at least 22 were found. */
MATCH s32 func_801E1C10(void) {
    s32 value;
    s32 count;
    s32 i;

    value = 0x38;
    count = 0;
    do {
        i = 0;
        do {
            if (g_SaveData.inventory_ids[0][i] == value && g_SaveData.inventory_counts[0][i] == 0x63) {
                count += 1;
            }
            i += 1;
        } while (i < 128);
        value += 1;
    } while (value < 78);
    return count >= 22;
}
