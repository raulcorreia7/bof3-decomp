#include "battle_03.h"

/* counts every queued attacker's item action, marks each battler
 * the overlay still holds, gates the selection flag and starts the overlay's
 * stream slot.
 */
MATCH void func_801D25A0(void) {
    s32  i;
    u8   rank;
    u16* flags;

    g_BattleMessageState = 2;
    i                    = 0;
    if ((s8)g_BattleCommandCount > 0) {
        do {
            rank = D_801462F6[i & BYTE_MASK];
            if ((rank != GAME_NONE) && ((Battle_SlotIsBlocked(rank) & BYTE_MASK) == 0)) {
                if (g_BattlePartyBattlers[rank].turn.command.type == 5) {
                    func_801DDE7C(g_BattlePartyBattlers[rank].turn.choice, g_BattlePartyBattlers[rank].turn.command.id);
                }
            }
            i += 1;
        } while ((i & BYTE_MASK) < (s8)g_BattleCommandCount);
    }
    i = 0;
    if (g_BattlePartyCount != 0) {
        do {
            if (((Battle_SlotIsBlocked(i & BYTE_MASK) & BYTE_MASK) == 0) &&
                ((g_BattleActionLock == 0) || ((g_BattlePartyBattlers[i & BYTE_MASK].turn.action_flags.value &
                                                COMBATANT_FLAG_SUPPRESSION_EXEMPT) != 0))) {
                g_BattlePartyBattlers[i & BYTE_MASK].header.mode = 2;
            }
            i += 1;
        } while ((u32)(i & BYTE_MASK) < g_BattlePartyCount);
    }
    BATTLE_RAISE_STATE(BATTLE_STATE_COMMAND_ARMED);
    EMI_LoaderStreamInitSlot(EMI_SLOT_BATL_SE);
    g_BattleStep    = 0;
    g_BattleSubStep = 0;
}
