#include "engine/slus/slus.h"

/* advances the record halfword toward its limit by delta, clamping
 * at the limit.
 */
MATCH s32 Char_RestoreAP(s32 character_index, s32 amount, s32 use_battle_copy) {
    Character* rec;
    s32        cur;
    s32        limit;

    if ((use_battle_copy & 0xFF) == 0) {
        rec = &g_Characters[character_index & 0xFF];
    } else {
        rec = (Character*)&D_80145F04[(character_index & 0xFF) * 0x140];
    }
    cur = rec->ap;
    if (cur == rec->stats.max_ap) {
        return 0;
    }
    rec->ap = (u16)(cur + amount);
    limit   = rec->stats.max_ap;
    if (((u32)limit < (u32)((cur + amount) & 0xFFFF)) || ((amount & 0xFFFF) == 0)) {
        rec->ap = limit;
    }
    return 1;
}
