#include "engine/slus/slus.h"

/* scans the 0x20-byte table g_SaveData.vital_item_ids for (item_id & 0xFF), returning
 * 1 on a hit and 0 otherwise.
 */
MATCH bool Item_VitalHas(s32 item_id) {
    u8* entry;
    s32 index;

    entry = g_SaveData.vital_item_ids;
    index = 0;
    while ((index & BYTE_MASK) < 32U) {
        if ((item_id & BYTE_MASK) == *entry) {
            return true;
        }
        index += 1;
        entry += 1;
    }
    return false;
}
