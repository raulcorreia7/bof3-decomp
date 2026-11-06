#include "engine/slus/slus.h"

/* returns the group's u16 resource id for one choice entry from the row table that the low byte of
 * category selects (strides 0x12 for 0 and others, 0x18, 0x16, 0x14, 0x10 for 1-4), indexed by the low byte of
 * item_id.
 */
MATCH s32 Item_GetDescription(s32 category, s32 item_id) {
    switch (category & 0xFF) {
        case ITEM_CAT_ITEM:
        default:
            return *(u16*)(&D_801C8972 + ((item_id & 0xFF) * 0x12));
        case ITEM_CAT_WEAPON:
            return *(u16*)(&D_801C90F0 + ((item_id & 0xFF) * 0x18));
        case ITEM_CAT_ARMOR:
            return *(u16*)(&D_801C98B6 + ((item_id & 0xFF) * 0x16));
        case ITEM_CAT_ACCESSORY:
            return *(u16*)(&D_801C9E8C + ((item_id & 0xFF) * 0x14));
        case ITEM_CAT_VITAL:
            return *(u16*)(&D_801C8FE8 + ((item_id & 0xFF) * 0x10));
    }
}
