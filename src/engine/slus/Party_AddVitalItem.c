#include "engine/slus/slus.h"

/* stores item_id in the first empty slot of the 0x20-byte table at
 * g_VitalItemIds, returning 1, or 0 when the table is full.
 */
MATCH s32 Party_AddVitalItem(u8 item_id) {
    u8* entry;
    u32 index;

    entry = g_VitalItemIds;
    index = 0;
    while ((u32)(index & BYTE_MASK) < 32U) {
        if (*entry == 0) {
            *entry = item_id;
            return 1;
        }
        index += 1;
        entry += 1;
    }
    return 0;
}
