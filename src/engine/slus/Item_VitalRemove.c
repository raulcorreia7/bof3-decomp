#include "engine/slus/slus.h"

/* scans the 32-entry table g_VitalItemIds for the low byte of item_id,
 * clears the matching entry, and reports whether one was found.
 */
MATCH s32 Item_VitalRemove(s32 item_id) {
    u8* entry;
    s32 index;

    entry = g_VitalItemIds;
    index = 0;
    while ((index & 0xFF) < 32U) {
        if (*entry == (item_id & 0xFF)) {
            *entry = 0;
            return 1;
        }
        index += 1;
        entry += 1;
    }
    return 0;
}
