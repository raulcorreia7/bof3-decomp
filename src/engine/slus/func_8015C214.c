#include "engine/slus/slus.h"

/* writes the 0x140-stride record flags selected by slot.
 */
MATCH void func_8015C214(s32 slot, u8 value) {
    u32 index;

    index             = (slot & BYTE_MASK) * 0x140;
    D_80145E91[index] = 2;
    D_80145E92[index] = 8;
    D_80145E93[index] = 0;
    D_80145E9B[index] = value;
}
