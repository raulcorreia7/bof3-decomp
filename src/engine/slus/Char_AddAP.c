#include "engine/slus/slus.h"

/* advances the count halfword at 0x16 of the g_Characters record by the caller's step, clamping back to the stored limit when it would overshoot. */
MATCH void Char_AddAP(s32 amount, s32 char_id) {
    Character* rec;
    u16        cur;
    u16        limit;
    u16        next;

    rec   = &g_Characters[g_CharSlot[char_id & BYTE_MASK]];
    cur   = rec->ap;
    limit = rec->stats.max_ap;
    if (cur < limit) {
        next    = cur + amount;
        rec->ap = next;
        if (rec->stats.max_ap < (next & HALF_MASK)) {
            rec->ap = rec->stats.max_ap;
        }
    }
}
