#include "engine/slus/slus.h"

MATCH bool Char_RestoreHP(s32 character_index, s32 amount, s32 use_battle_copy) {
    Character* rec;
    s32        cur;
    s32        limit;

    if ((use_battle_copy & BYTE_MASK) == 0) {
        rec = &g_SaveData.characters[character_index & BYTE_MASK];
    } else {
        rec = (Character*)&D_80145F04[(character_index & BYTE_MASK) * 0x140];
    }
    cur = rec->hp;
    if (cur == rec->stats.max_hp) {
        return false;
    }
    rec->hp = (u16)(cur + amount);
    limit   = rec->stats.max_hp;
    if (((u32)limit < (u32)((cur + amount) & HALF_MASK)) || ((amount & HALF_MASK) == 0)) {
        rec->hp = (u16)limit;
    }
    if (rec->hp >= (u32)(rec->stats.max_hp >> 2)) {
        Char_ClearStatus(character_index & BYTE_MASK, 0x2000, use_battle_copy & BYTE_MASK);
    }
    return true;
}
