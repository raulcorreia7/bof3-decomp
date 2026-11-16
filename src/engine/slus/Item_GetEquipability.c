#include "engine/slus/slus.h"

/* returns byte 0 of the record `category`/`item` selects: 24-byte D_801C90E8 (category 1), 22-byte D_801C98B0 (category
 * 2), 20-byte D_801C9E88 (category 3); the other categories return 0xFF. Item_GetFlags and Item_GetIcon read the
 * flags and type bytes of the same rows. */
MATCH u8 Item_GetEquipability(u8 category, u8 item) {
    switch (category) {
        case ITEM_CATEGORY_WEAPON:
            return D_801C90E8[(item & BYTE_MASK) * 0x18];
        case ITEM_CATEGORY_ARMOR:
            return D_801C98B0[(item & BYTE_MASK) * 0x16];
        case ITEM_CATEGORY_ACCESSORY:
            return D_801C9E88[(item & BYTE_MASK) * 0x14];
        case ITEM_CATEGORY_ITEM:
        case ITEM_CATEGORY_VITAL:
        default:
            return 0xFF;
    }
}
