#include "engine/slus/slus.h"

/* The description message id of a row. The category selects the item, weapon, armor, accessory or vital-item
 * table.
 */
MATCH s32 Item_GetDescription(s32 category, s32 item_id) {
    switch (category & BYTE_MASK) {
        case ITEM_CATEGORY_ITEM:
        default:
            return g_Items[item_id & BYTE_MASK].description;
        case ITEM_CATEGORY_WEAPON:
            return g_Weapons[item_id & BYTE_MASK].description;
        case ITEM_CATEGORY_ARMOR:
            return g_Armors[item_id & BYTE_MASK].description;
        case ITEM_CATEGORY_ACCESSORY:
            return g_Accessories[item_id & BYTE_MASK].description;
        case ITEM_CATEGORY_VITAL:
            return g_VitalItems[item_id & BYTE_MASK].description;
    }
}
