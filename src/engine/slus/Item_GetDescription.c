#include "engine/slus/slus.h"

/* The description message id of a row. The category selects the item, weapon, armor, accessory or vital-item
 * table, whose strides are 0x12, 0x18, 0x16, 0x14 and 0x10.
 */
MATCH s32 Item_GetDescription(s32 category, s32 item_id) {
    switch (category & BYTE_MASK) {
        case ITEM_CATEGORY_ITEM:
        default:
            return *(u16*)(&D_801C8972 + ((item_id & BYTE_MASK) * 0x12));
        case ITEM_CATEGORY_WEAPON:
            return *(u16*)(&D_801C90F0 + ((item_id & BYTE_MASK) * 0x18));
        case ITEM_CATEGORY_ARMOR:
            return *(u16*)(&D_801C98B6 + ((item_id & BYTE_MASK) * 0x16));
        case ITEM_CATEGORY_ACCESSORY:
            return *(u16*)(&D_801C9E8C + ((item_id & BYTE_MASK) * 0x14));
        case ITEM_CATEGORY_VITAL:
            return *(u16*)(&D_801C8FE8 + ((item_id & BYTE_MASK) * 0x10));
    }
}
