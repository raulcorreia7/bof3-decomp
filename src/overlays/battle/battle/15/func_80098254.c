#include "battle_15.h"

MATCH void func_80098254(void) {
    u8 counter;

    SND_PlayCue(EMI_CUE_ID(1, 4));
    g_Battle.selection_latch        = 0;
    g_BattleActorTurn->command.type = 0;
    g_BattleActorTurn->damage_flags.value |= COMBATANT_FLAG_COMMAND_ENTERED;

    BATTLE_ACTIVE_ROW->header.mode = 2;
    counter                        = g_Battle.command_count;
    g_Battle.phase.step            = 1;
    g_Battle.phase.sub_step        = 0;
    g_Battle.ui_step               = 0;
    g_Battle.command_count         = counter + 1;
}
