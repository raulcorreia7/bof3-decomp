#include "engine/slus/slus.h"

/* returns byte 1 of the record `category`/`item` selects. */
MATCH u32 Item_GetFlags(u32 category, u32 item) {
    switch (category & BYTE_MASK) {
        case ITEM_CAT_ITEM:
        default:
            return D_801C8970[(item & BYTE_MASK) * 0x12];
        case ITEM_CAT_WEAPON:
            return D_801C90E9[(item & BYTE_MASK) * 0x18];
        case ITEM_CAT_ARMOR:
            return D_801C98B1[(item & BYTE_MASK) * 0x16];
        case ITEM_CAT_ACCESSORY:
            return D_801C9E89[(item & BYTE_MASK) * 0x14];
        case ITEM_CAT_VITAL:
            return 0;
    }
}
