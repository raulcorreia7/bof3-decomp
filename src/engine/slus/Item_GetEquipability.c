#include "engine/slus/slus.h"

/* returns byte 0 of the record `category`/`item` selects: 24-byte D_801C90E8 (category 1), 22-byte D_801C98B0
 * (category 2), 20-byte D_801C9E88 (category 3); other kinds return 0xFF. Item_GetFlags and Item_GetKind read bytes 1 and 2
 * of the same tables.
 */
MATCH u8 Item_GetEquipability(u8 category, u8 item) {
    switch (category) {
        case ITEM_CAT_WEAPON:
            return D_801C90E8[(item & 0xFF) * 0x18];
        case ITEM_CAT_ARMOR:
            return D_801C98B0[(item & 0xFF) * 0x16];
        case ITEM_CAT_ACCESSORY:
            return D_801C9E88[(item & 0xFF) * 0x14];
        case ITEM_CAT_ITEM:
        case ITEM_CAT_VITAL:
        default:
            return 0xFF;
    }
}
