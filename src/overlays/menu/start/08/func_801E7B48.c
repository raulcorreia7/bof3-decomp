#include "start_08.h"

MATCH s32 func_801E7B48(s32 caster_index, s32 target_index, s32 use_battle_record) {
    u32 index;
    u8  count;
    s32 i;
    s32 found;
    s32 character_offset;
    s32 use_battle_copy;
    s32 result;

    use_battle_copy  = use_battle_record;
    found            = 0;
    i                = 0;
    character_offset = (caster_index & BYTE_MASK) * 0xA4;
    for (;;) {
        count = Party_CountOrder(PARTY_ORDER_FIELD);
        index = i & BYTE_MASK;
        if (index >= count) {
            break;
        }
        i++;
        found |= Char_RestoreHP(
            D_80145FCC[index][0],
            ((*(u16*)((u8*)&g_Characters[0].stats.intellect + character_offset) + 0x64) * 0x78 / 100) & HALF_MASK,
            use_battle_copy & BYTE_MASK);
    }
    result = 4;
    if (found & BYTE_MASK) {
        result = 1;
    }
    return result;
}
