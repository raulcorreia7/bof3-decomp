#include "engine/slus/slus.h"

/* advances the count halfword at 0x16 of the g_Characters record by the
 * caller's step, clamping back to the stored limit when it would overshoot.
 */
MATCH void Char_AddAp(s32 amount, s32 char_id) {
    Character* rec;
    u16        cur;
    u16        limit;
    u16        next;

    rec   = &g_Characters[g_CharSlot[char_id & BYTE_MASK]];
    cur   = rec->current_ap;
    limit = rec->max_ap;
    if (cur < limit) {
        next            = cur + amount;
        rec->current_ap = next;
        if (rec->max_ap < (next & HALF_MASK)) {
            rec->current_ap = rec->max_ap;
        }
    }
}
