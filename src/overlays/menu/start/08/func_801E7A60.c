#include "start_08.h"

MATCH s32 func_801E7A60(s32 character_index, s32 intellect_step, s32 slot_count) {
    u32 offset;
    u8  index;
    u8  updated;
    u16 amount;
    s32 result;

    updated = 0;
    index   = 0;
    offset  = (character_index & BYTE_MASK) * 0xA4;
    for (; index < Party_CountOrder(PARTY_ORDER_KIND_WALKING); index++) {
        amount = (((*(u16*)((u8*)&g_Characters[0].stats.intellect + offset) + 0x64) * 0x28) / 100);
        updated |= Char_RestoreHP(D_80145FCC[index][0], amount, slot_count & BYTE_MASK);
    }
    result = 4;
    if (updated) {
        result = 1;
    }
    return result;
}
