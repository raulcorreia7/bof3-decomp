#include "battle_15.h"

MATCH void func_80098254(void) {
    u8 counter;

    SND_PlayCue(EMI_CUE_ID(1, 4));
    g_BattleSelectionLatch          = 0;
    g_BattleActorTurn->command.type = 0;
    g_BattleActorTurn->damage_flags.value |= COMBATANT_FLAG_COMMAND_ENTERED;

    BATTLE_ACTIVE_ROW->header.mode = 2;
    counter                        = g_BattleCommandCount;
    g_BattleStep                   = 1;
    g_BattleSubStep                = 0;
    g_BattleUIStep                 = 0;
    g_BattleCommandCount           = counter + 1;
}
