#include "battle_15.h"

MATCH void func_800A581C(void) {
    u8* counter;

    SND_PlayCue(EMI_CUE_ID(1, 4));
    D_80148627 = 2;
    BATTLE_ACTIVE_ROW->turn.action_flags.volatile_value |= 4;
    counter  = (u8*)&g_BattleUIState;
    *counter = *counter + 1;
}
