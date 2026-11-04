#include "engine/slus/slus.h"

/* adds amount to current_hp of the record char_id indexes through g_CharSlot, clamped to max_hp; clears bit 0x2000 of status in the record
 * indexed by work byte +0x13C and in the work area's +0x80 when its max_hp >> 2 is below current_hp.
 */
MATCH void Char_AddHp(s32 amount, u8 char_id) {
    Character* record;
    s32        slot;
    u16        value;

    record = &g_Characters[g_CharSlot[char_id]];
    value  = record->current_hp;
    if (value < record->max_hp) {
        record->current_hp = value + amount;
        if (record->max_hp < (u16)(value + amount)) {
            record->current_hp = record->max_hp;
        }
        slot = g_GameState->unk_13A[2];
        if ((g_Characters[slot].max_hp >> 2) < g_Characters[slot].current_hp) {
            g_Characters[slot].status &= ~STATUS_LOW_HP;
            g_GameState->stats.status &= ~STATUS_LOW_HP;
        }
    }
}
