#include "battle_15.h"

/* sets flag bit 0x10 on the player row named by g_Battle.target, marks
 * the battle sub-state byte 4, then walks selection slots from
 * g_Battle.turn_cursor-1 up to g_Battle.turn_count: each slot byte that is not
 * 0xFF is sent to func_801DDFEC and marked 0xFF.
 */
MATCH void func_800A0920(void) {
    s32 base;
    u32 slot;

    Battle_MarkDamageApplied();
    g_Game.members[g_Battle.target].u.turn.action_flags.volatile_value |= COMBATANT_FLAG_SUPPRESSION_EXEMPT;
    base                 = g_Battle.turn_cursor - 1;
    g_Battle.action_lock = 4;
    slot                 = base & BYTE_MASK;
    if (g_Battle.turn_count >= slot) {
        do {
            if (g_Battle.turn_order[slot] != GAME_NONE) {
                func_801DDFEC(slot);
                g_Battle.turn_order[slot] = 0xFF;
            }
            base += 1;
            slot = base & BYTE_MASK;
        } while (g_Battle.turn_count >= slot);
    }
}
