#include "engine/slus/slus.h"

/* returns the low nibble of the record's kind byte: the icon of an item, weapon or accessory, the slot of an armor. */
MATCH s32 Item_GetKind(s32 category, s32 item_id) {
    switch (category & BYTE_MASK) {
        case ITEM_CAT_ITEM:
        default:
            return g_Items[item_id & BYTE_MASK].kind & 0xF;
        case ITEM_CAT_WEAPON:
            return g_Weapons[item_id & BYTE_MASK].kind & 0xF;
        case ITEM_CAT_ARMOR:
            return g_Armors[item_id & BYTE_MASK].equip_type & 0xF;
        case ITEM_CAT_ACCESSORY:
            return g_Accessories[item_id & BYTE_MASK].kind & 0xF;
    }
}
