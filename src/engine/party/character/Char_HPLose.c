#include "engine/slus/slus.h"

/* clamps `amount` to one below the selected character's HP, debits that amount and, when the limit in
 * quarter units no longer covers the gauge, raises bit 0x2000 on the record's flags and the work area's +0x80;
 * returns the clamped amount as 16 bits.
 */
MATCH u16 Char_HPLose(s32 amount, s32 character_id) {
    PartyMember* block;
    u16          count;
    s32          slot;

    slot  = g_CharSlot[(u8)character_id];
    count = g_Characters[slot].hp;
    if ((u16)amount >= count) {
        amount = count - 1;
    }

    slot                  = g_CharSlot[character_id & BYTE_MASK];
    count                 = g_Characters[slot].hp;
    g_Characters[slot].hp = count - amount;

    block = g_GameState;
    slot  = block->unk_13A[2];
    if ((g_Characters[slot].stats.max_hp >> 2) >= g_Characters[slot].hp) {
        g_Characters[slot].status |= STATUS_LOW_HP;
        block->chr.status |= STATUS_LOW_HP;
    }
    return amount & HALF_MASK;
}
