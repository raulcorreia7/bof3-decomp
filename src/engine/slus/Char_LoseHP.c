#include "engine/slus/slus.h"

/* clamps `mode` to one below the selected character's gauge, debits that amount and. */
MATCH u16 Char_LoseHP(s32 mode, s32 index) {
    PartyMember* block;
    u16          count;
    s32          slot;

    slot  = g_CharSlot[(u8)index];
    count = g_Characters[slot].hp;
    if ((u16)mode >= count) {
        mode = count - 1;
    }

    slot                  = g_CharSlot[index & BYTE_MASK];
    count                 = g_Characters[slot].hp;
    g_Characters[slot].hp = count - mode;

    block = g_GameState;
    slot  = block->unk_13A[2];
    if ((g_Characters[slot].stats.max_hp >> 2) >= g_Characters[slot].hp) {
        g_Characters[slot].status |= STATUS_LOW_HP;
        block->chr.status |= STATUS_LOW_HP;
    }
    return mode & HALF_MASK;
}
