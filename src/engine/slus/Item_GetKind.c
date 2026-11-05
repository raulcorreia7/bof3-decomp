#include "engine/slus/slus.h"

/* returns the low nibble of byte 2 of the record `category`/`item_id` selects: 18-byte rows of D_801C8971 (category 0
 * and others), 24-byte D_801C90EA (category 1), 22-byte D_801C98B2 (category 2), 20-byte D_801C9E8A (category 3).
 */
MATCH s32 Item_GetKind(s32 category, s32 item_id) {
    switch (category & BYTE_MASK) {
        case ITEM_CAT_ITEM:
        default:
            return D_801C8971[(item_id & BYTE_MASK) * 0x12] & 0xF;
        case ITEM_CAT_WEAPON:
            return D_801C90EA[(item_id & BYTE_MASK) * 0x18] & 0xF;
        case ITEM_CAT_ARMOR:
            return D_801C98B2[(item_id & BYTE_MASK) * 0x16] & 0xF;
        case ITEM_CAT_ACCESSORY:
            return D_801C9E8A[(item_id & BYTE_MASK) * 0x14] & 0xF;
    }
}
