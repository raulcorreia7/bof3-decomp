#include "engine/slus/slus.h"

/* Armor uses its equip type as the icon index. */
MATCH s32 Item_GetIcon(ItemCategory category, s32 item_id) {
    s32 category_byte;

    category_byte = category;
    switch (category_byte & BYTE_MASK) {
        case ITEM_CAT_ITEM:
        default:
            return g_Items[item_id & BYTE_MASK].icon & 0xF;
        case ITEM_CAT_WEAPON:
            return g_Weapons[item_id & BYTE_MASK].icon & 0xF;
        case ITEM_CAT_ARMOR:
            return g_Armors[item_id & BYTE_MASK].equip_type & 0xF;
        case ITEM_CAT_ACCESSORY:
            return g_Accessories[item_id & BYTE_MASK].icon & 0xF;
    }
}
