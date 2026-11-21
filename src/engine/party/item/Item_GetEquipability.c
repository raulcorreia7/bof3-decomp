#include "engine/slus/slus.h"

/* returns the equipability byte of the weapon, armor or accessory row `category`/`item` selects; the other categories
 * return 0xFF. Item_GetFlags and Item_GetIcon read the flags and type bytes of the same rows. */
MATCH u8 Item_GetEquipability(u8 category, u8 item) {
    switch (category) {
        case ITEM_CATEGORY_WEAPON:
            return g_Weapons[item & BYTE_MASK].header.equipability;
        case ITEM_CATEGORY_ARMOR:
            return g_Armors[item & BYTE_MASK].header.equipability;
        case ITEM_CATEGORY_ACCESSORY:
            return g_Accessories[item & BYTE_MASK].header.equipability;
        case ITEM_CATEGORY_ITEM:
        case ITEM_CATEGORY_VITAL:
        default:
            return 0xFF;
    }
}
