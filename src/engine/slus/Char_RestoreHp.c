#include "engine/slus/slus.h"

/* advances the record halfword toward its limit by delta, clamping
 * at the limit, and notifies once the value reaches a quarter of the limit.
 */
MATCH bool Char_RestoreHp(s32 character_index, s32 amount, s32 use_battle_copy) {
    Character* rec;
    s32        cur;
    s32        limit;

    if ((use_battle_copy & BYTE_MASK) == 0) {
        rec = &g_Characters[character_index & BYTE_MASK];
    } else {
        rec = (Character*)&D_80145F04[(character_index & BYTE_MASK) * 0x140];
    }
    cur = rec->current_hp;
    if (cur == rec->max_hp) {
        return false;
    }
    rec->current_hp = (u16)(cur + amount);
    limit           = rec->max_hp;
    if (((u32)limit < (u32)((cur + amount) & HALF_MASK)) || ((amount & HALF_MASK) == 0)) {
        rec->current_hp = (u16)limit;
    }
    if (rec->current_hp >= (u32)(rec->max_hp >> 2)) {
        Char_ClearStatus(character_index & BYTE_MASK, 0x2000, use_battle_copy & BYTE_MASK);
    }
    return true;
}
