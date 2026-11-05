#include "battle_15.h"

/* sets flag bit 0x10 on the player row named by g_BattleTarget, marks
 * the battle sub-state byte 4, then walks selection slots from
 * D_80146322-1 up to D_80146323: each slot byte that is not
 * 0xFF is sent to func_801DDFEC and marked 0xFF.
 */
MATCH void func_800A0920(void) {
    s32 base;
    u32 slot;

    func_800A3F28();
    g_BattlePartyBattlers[g_BattleTarget].action_flags.volatile_value |= COMBATANT_FLAG_SUPPRESSION_EXEMPT;
    base               = D_80146322 - 1;
    g_BattleActionLock = 4;
    slot               = base & BYTE_MASK;
    if (D_80146323 >= slot) {
        do {
            if (D_8014630C[slot] != GAME_NONE) {
                func_801DDFEC(slot);
                D_8014630C[slot] = 0xFF;
            }
            base += 1;
            slot = base & BYTE_MASK;
        } while (D_80146323 >= slot);
    }
}
