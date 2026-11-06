#include "engine/slus/slus.h"

MATCH bool Char_RestoreHP(s32 character_index, s32 amount, s32 use_battle_copy) {
    Character* rec;
    s32        cur;
    s32        limit;

    if ((use_battle_copy & 0xFF) == 0) {
        rec = &g_Characters[character_index & 0xFF];
    } else {
        rec = (Character*)&D_80145F04[(character_index & 0xFF) * 0x140];
    }
    cur = rec->hp;
    if (cur == rec->stats.max_hp) {
        return false;
    }
    rec->hp = (u16)(cur + amount);
    limit   = rec->stats.max_hp;
    if (((u32)limit < (u32)((cur + amount) & 0xFFFF)) || ((amount & 0xFFFF) == 0)) {
        rec->hp = (u16)limit;
    }
    if (rec->hp >= (u32)(rec->stats.max_hp >> 2)) {
        Char_ClearStatus(character_index & 0xFF, 0x2000, use_battle_copy & 0xFF);
    }
    return true;
}
