#include "engine/slus/slus.h"

/* clamps requested to the selected character's gauge, subtracts the clamped amount and returns it as 16 bits.
 * Both the slot map and the gauge are read twice, so the second lookup carries its own mask spelling.
 */
MATCH s32 Char_SpendAp(s32 requested, s32 character_id) {
    u16 gauge;
    s32 amount;
    s32 slot;

    slot   = g_CharSlot[(u8)character_id];
    gauge  = g_Characters[slot].current_ap;
    amount = requested;
    if ((u16)amount >= gauge) {
        amount = gauge - 1;
    }
    slot = g_CharSlot[character_id & BYTE_MASK];
    g_Characters[slot].current_ap -= amount;
    return (u16)amount;
}
