#include "battle_15.h"

MATCH void func_800A581C(void) {
    u8* counter;

    SND_PlayCue(EMI_CUE_ID(1, 4));
    D_80148627 = 2;
    BATTLE_ACTIVE_ROW->u.turn.action_flags.volatile_value |= COMBATANT_FLAG_ABILITY_ALT_POSE;
    counter  = (u8*)&g_Battle.ui_state;
    *counter = *counter + 1;
}
