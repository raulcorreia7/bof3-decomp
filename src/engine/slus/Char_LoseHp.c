#include "engine/slus/slus.h"

/* clamps `mode` to one below the selected character's gauge, debits that amount and, when the limit in
 * quarter units no longer covers the gauge, raises bit 0x2000 on the record's flags and the work area's +0x80;
 * returns the clamped mode as 16 bits.
 */
MATCH s32 Char_LoseHp(s32 mode, s32 index) {
    PartyBattler* block;
    u16           count;
    s32           slot;

    slot  = g_CharSlot[(u8)index];
    count = g_Characters[slot].current_hp;
    if ((u16)mode >= count) {
        mode = count - 1;
    }

    slot                          = g_CharSlot[index & BYTE_MASK];
    count                         = g_Characters[slot].current_hp;
    g_Characters[slot].current_hp = count - mode;

    block = g_GameState;
    slot  = block->unk_13A[2];
    if ((g_Characters[slot].max_hp >> 2) >= g_Characters[slot].current_hp) {
        g_Characters[slot].status |= STATUS_LOW_HP;
        block->stats.status |= STATUS_LOW_HP;
    }
    return mode & HALF_MASK;
}
