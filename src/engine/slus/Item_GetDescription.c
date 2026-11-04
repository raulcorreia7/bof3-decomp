#include "engine/slus/slus.h"

/* returns the group's u16 resource id for one choice entry from the row table that the low byte of
 * group_index selects (strides 0x12 for 0 and others, 0x18, 0x16, 0x14, 0x10 for 1-4), indexed by the low byte of
 * choice_entry.
 */
MATCH s32 Item_GetDescription(s32 group_index, s32 choice_entry) {
    switch (group_index & BYTE_MASK) {
        case 0:
        default:
            return *(u16*)(&D_801C8972 + ((choice_entry & BYTE_MASK) * 0x12));
        case 1:
            return *(u16*)(&D_801C90F0 + ((choice_entry & BYTE_MASK) * 0x18));
        case 2:
            return *(u16*)(&D_801C98B6 + ((choice_entry & BYTE_MASK) * 0x16));
        case 3:
            return *(u16*)(&D_801C9E8C + ((choice_entry & BYTE_MASK) * 0x14));
        case 4:
            return *(u16*)(&D_801C8FE8 + ((choice_entry & BYTE_MASK) * 0x10));
    }
}
