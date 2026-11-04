#include "engine/slus/slus.h"

/* returns byte 6 of the category-1 record and byte 4 of the category-2 record
 * selected by `item`, using the 24-byte D_801C90E8 and 22-byte D_801C98B0
 * tables the paired accessors Item_GetEquipability/Item_GetKind/Item_GetFlags read.
 * Kind 0 and every other category return 0.
 */
MATCH u8 Item_GetPower(u8 category, u8 item) {
    switch (category) {
        case 0:
        default:
            return 0;
        case 1:
            return D_801C90E8[(item & BYTE_MASK) * 0x18 + 6];
        case 2:
            return D_801C98B0[(item & BYTE_MASK) * 0x16 + 4];
    }
}
