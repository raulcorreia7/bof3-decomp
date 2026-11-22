#include "battle_15.h"

/* scans the three local battle records: live slots with the pending
 * flag either arm the selection action bit or clear the flag, and the routine
 * reports whether it armed one. */
MATCH s32 func_800AA8FC(void) {
    s32 i;
    s32 off;
    s32 result;
    u32 flags;
    u16 type;
    u8  slot;

    result = 0;
    for (i = 0; (i & BYTE_MASK) < 3U; i++) {
        slot = i;
        if ((Battle_SlotIsBlocked(slot) & BYTE_MASK) == 0) {
            off   = slot * BATTLE_PARTY_STRIDE;
            flags = g_Game.members[slot].u.turn.damage_flags.value;
            if (flags & 0x8) {
                if ((func_800AA874((u8)g_Battle.action->unk_02) & BYTE_MASK) == 0) {
                    type = g_Battle.action->unk_02;
                    if (D_801CA71C[type].mask & 0x200) {
                        Char_AbilityAdd(type, slot, 0, 1);
                        Char_AbilityAdd(g_Battle.action->unk_02, (&g_Game.members[0].character_index)[off], 0, 0);
                        type = g_Battle.action->unk_02;
                        BIT_ARRAY_SET(g_LearnedAbilities, type);
                    }
                    result = 1;
                }
            } else {
                g_Game.members[slot].u.turn.damage_flags.value = flags & ~8;
            }
        }
    }
    return result;
}
