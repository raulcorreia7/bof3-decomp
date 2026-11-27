#include "battle_15.h"

/* func_80097DC0 */
MATCH void Battle_ToggleAbilityTargetSide(void) {
    u16 held;
    u8* message;
    u8* entry;

    held = g_PadStates[0].pressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_Battle.ui_mode = 3u;
    } else if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_Battle.ui_mode = 2u;
    } else if ((INPUT_REPEATED(held, INPUT_DIRECTIONAL) & INPUT_DIRECTIONAL) != 0) {
        /* FAKE: plain read of the message-slot selector: the volatile qualifier
         * makes the scheduler fill the branch delay slot and shifts the call. */
        message = (u8*)&D_80148656;
        entry   = Party_GetAbilities(message[0], g_UIPanelTasks[16].unk_0B, 1);
        if ((g_Abilities[entry[g_UIPanelTasks[16].unk_0C]].targeting_flags & ABILITY_TARGET_FLAG_BOTH_SIDES) != 0u) {
            g_BattleActorTurn->command.target ^= BATTLE_TARGET_BOTH_SIDES;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        }
    }
}
