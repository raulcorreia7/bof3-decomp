#include "engine/slus/slus.h"

/* The flags byte of the row the category selects; a vital item has none. Item_GetEquipability and Item_GetIcon read
 * the equipability and type bytes of the same rows. */
MATCH u32 Item_GetFlags(u32 category, u32 item) {
    switch (category & BYTE_MASK) {
        case ITEM_CATEGORY_ITEM:
        default:
            return g_Items[item & BYTE_MASK].flags;
        case ITEM_CATEGORY_WEAPON:
            return g_Weapons[item & BYTE_MASK].header.flags;
        case ITEM_CATEGORY_ARMOR:
            return g_Armors[item & BYTE_MASK].header.flags;
        case ITEM_CATEGORY_ACCESSORY:
            return g_Accessories[item & BYTE_MASK].header.flags;
        case ITEM_CATEGORY_VITAL:
            return 0;
    }
}
