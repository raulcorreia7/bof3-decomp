#include "battle_03.h"

/* counts every queued attacker's item action, marks each battler
 * the overlay still holds, gates the selection flag and starts the overlay's
 * stream slot.
 */
/* func_801D25A0 */
MATCH void Battle_ArmCommands(void) {
    s32  i;
    u8   rank;
    u16* flags;

    g_BattleMessageState = 2;
    i                    = 0;
    if ((s8)g_Battle.command_count > 0) {
        do {
            rank = D_801462F6[i & BYTE_MASK];
            if ((rank != GAME_NONE) && ((Battle_SlotIsBlocked(rank) & BYTE_MASK) == 0)) {
                if (g_Game.members[rank].u.turn.command.type == BATTLE_COMMAND_ITEM) {
                    func_801DDE7C(g_Game.members[rank].u.turn.choice, g_Game.members[rank].u.turn.command.id);
                }
            }
            i += 1;
        } while ((i & BYTE_MASK) < (s8)g_Battle.command_count);
    }
    i = 0;
    if (g_Battle.party_count != 0) {
        do {
            if (((Battle_SlotIsBlocked(i & BYTE_MASK) & BYTE_MASK) == 0) &&
                ((g_Battle.action_lock == 0) || ((g_Game.members[i & BYTE_MASK].u.turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) != 0))) {
                g_Game.members[i & BYTE_MASK].header.mode = 2;
            }
            i += 1;
        } while ((u32)(i & BYTE_MASK) < g_Battle.party_count);
    }
    BATTLE_RAISE_STATE(BATTLE_STATE_COMMAND_ARMED);
    EMI_LoadArchive(EMI_SLOT_BATL_SE);
    g_Battle.phase.step     = 0;
    g_Battle.phase.sub_step = 0;
}
