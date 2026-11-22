#include "battle_15.h"

/* func_80096E14 */
MATCH void Battle_ConfirmAttack(void) {
    u8 counter;

    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
    g_Battle.selection_latch        = 0;
    g_BattleActorTurn->command.type = BATTLE_COMMAND_ATTACK;

    BATTLE_ACTIVE_ROW->header.mode = 2;
    counter                        = g_Battle.command_count;
    g_Battle.phase.step            = 1;
    g_Battle.phase.sub_step        = 0;
    g_Battle.ui_step               = 0;
    g_Battle.ui_mode               = 0;
    g_Battle.command_count         = counter + 1;
}
