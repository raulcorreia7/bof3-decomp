#include "engine/slus/slus.h"

/* The flags byte of the row: 18-byte item rows from D_801C8970, 24-byte weapon rows from D_801C90E9, 22-byte armor
 * rows from D_801C98B1, 20-byte accessory rows from D_801C9E89; a vital item has none. Item_GetEquipability and
 * Item_GetIcon read the equipability and type bytes of the same rows. */
MATCH u32 Item_GetFlags(u32 category, u32 item) {
    switch (category & BYTE_MASK) {
        case ITEM_CATEGORY_ITEM:
        default:
            return D_801C8970[(item & BYTE_MASK) * 0x12];
        case ITEM_CATEGORY_WEAPON:
            return D_801C90E9[(item & BYTE_MASK) * 0x18];
        case ITEM_CATEGORY_ARMOR:
            return D_801C98B1[(item & BYTE_MASK) * 0x16];
        case ITEM_CATEGORY_ACCESSORY:
            return D_801C9E89[(item & BYTE_MASK) * 0x14];
        case ITEM_CATEGORY_VITAL:
            return 0;
    }
}
