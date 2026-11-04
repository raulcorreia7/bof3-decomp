#include "engine/slus/slus.h"

/* scans the 0x20-byte table g_VitalItemIds for (item_id & 0xFF), returning
 * 1 on a hit and 0 otherwise.
 */
MATCH bool Party_HasVitalItem(s32 item_id) {
    u8* entry;
    s32 index;

    entry = g_VitalItemIds;
    index = 0;
    while ((u32)(index & BYTE_MASK) < 32U) {
        if ((item_id & BYTE_MASK) == *entry) {
            return true;
        }
        index += 1;
        entry += 1;
    }
    return false;
}
