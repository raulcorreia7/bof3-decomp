#include "engine/slus/slus.h"

/* returns the power of the weapon or armor row `item` selects; the paired accessors Item_GetEquipability,
 * Item_GetIcon and Item_GetFlags read the other members. Every other category returns 0.
 */
MATCH u8 Item_GetPower(u8 category, u8 item) {
    switch (category) {
        case ITEM_CATEGORY_ITEM:
        default:
            return 0;
        case ITEM_CATEGORY_WEAPON:
            return g_Weapons[item & BYTE_MASK].power;
        case ITEM_CATEGORY_ARMOR:
            return g_Armors[item & BYTE_MASK].power;
    }
}
