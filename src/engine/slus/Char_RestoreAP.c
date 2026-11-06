#include "engine/slus/slus.h"

/* advances the record halfword toward its limit by delta, clamping
 * at the limit.
 */
MATCH s32 Char_RestoreAP(s32 character_index, s32 amount, s32 mode) {
    Character* rec;
    s32        cur;
    s32        limit;

    if ((mode & BYTE_MASK) == 0) {
        rec = &g_Characters[character_index & BYTE_MASK];
    } else {
        rec = (Character*)&D_80145F04[(character_index & BYTE_MASK) * 0x140];
    }
    cur = rec->ap;
    if (cur == rec->stats.max_ap) {
        return 0;
    }
    rec->ap = (u16)(cur + amount);
    limit   = rec->stats.max_ap;
    if (((u32)limit < (u32)((cur + amount) & HALF_MASK)) || ((amount & HALF_MASK) == 0)) {
        rec->ap = limit;
    }
    return 1;
}
