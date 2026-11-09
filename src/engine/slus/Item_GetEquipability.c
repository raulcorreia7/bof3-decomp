#include "engine/slus/slus.h"

/* returns byte 0 of the record `category`/`item` selects. */
MATCH u8 Item_GetEquipability(u8 category, u8 item) {
    switch (category) {
        case ITEM_CAT_WEAPON:
            return D_801C90E8[(item & BYTE_MASK) * 0x18];
        case ITEM_CAT_ARMOR:
            return D_801C98B0[(item & BYTE_MASK) * 0x16];
        case ITEM_CAT_ACCESSORY:
            return D_801C9E88[(item & BYTE_MASK) * 0x14];
        case ITEM_CAT_ITEM:
        case ITEM_CAT_VITAL:
        default:
            return 0xFF;
    }
}
