#include "engine/slus/slus.h"

/* returns the low nibble of byte 2 of the record `kind`/`index` selects: 18-byte rows of D_801C8971 (kind 0
 * and others), 24-byte D_801C90EA (kind 1), 22-byte D_801C98B2 (kind 2), 20-byte D_801C9E8A (kind 3).
 */
MATCH s32 Item_GetKind(s32 kind, s32 index) {
    switch (kind & BYTE_MASK) {
        case 0:
        default:
            return D_801C8971[(index & BYTE_MASK) * 0x12] & 0xF;
        case 1:
            return D_801C90EA[(index & BYTE_MASK) * 0x18] & 0xF;
        case 2:
            return D_801C98B2[(index & BYTE_MASK) * 0x16] & 0xF;
        case 3:
            return D_801C9E8A[(index & BYTE_MASK) * 0x14] & 0xF;
    }
}
