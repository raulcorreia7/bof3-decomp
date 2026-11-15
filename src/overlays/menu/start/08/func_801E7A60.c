#include "start_08.h"

MATCH s32 func_801E7A60(s32 character_index, s32 intellect_step, s32 slot_count) {
    u8  index;
    u8  updated;
    u16 amount;
    s32 result;

    updated = 0;
    index   = 0;
    for (; index < Party_CountOrder(PARTY_ORDER_FIELD); index++) {
        amount = (((g_Characters[character_index & BYTE_MASK].stats.intellect + 0x64) * 0x28) / 100);
        updated |= Char_RestoreHP(g_Game.members[index].character_index, amount, slot_count & BYTE_MASK);
    }
    result = 4;
    if (updated) {
        result = 1;
    }
    return result;
}
