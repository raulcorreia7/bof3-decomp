#include "engine/slus/slus.h"

/* returns byte 1 of the record `category`/`item` selects: 18-byte rows of D_801C8970 (category 0 and others),
 * 24-byte D_801C90E9 (category 1), 22-byte D_801C98B1 (category 2), 20-byte D_801C9E89 (category 3); category 4 returns 0.
 * Item_GetEquipability and Item_GetKind read bytes 0 and 2.
 */
MATCH u32 Item_GetFlags(u32 category, u32 item) {
    switch (category & BYTE_MASK) {
        case 0:
        default:
            return D_801C8970[(item & BYTE_MASK) * 0x12];
        case 1:
            return D_801C90E9[(item & BYTE_MASK) * 0x18];
        case 2:
            return D_801C98B1[(item & BYTE_MASK) * 0x16];
        case 3:
            return D_801C9E89[(item & BYTE_MASK) * 0x14];
        case 4:
            return 0;
    }
}
