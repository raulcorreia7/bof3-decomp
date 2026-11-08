#include "battle_15.h"

/* func_800A581C */
MATCH void Battle_PlayAbilityPose(void) {
    u8* counter;

    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
    D_80148627 = 2;
    BATTLE_ACTIVE_ROW->u.turn.action_flags.volatile_value |= COMBATANT_FLAG_ABILITY_ALT_POSE;
    counter  = (u8*)&g_Battle.ui_state;
    *counter = *counter + 1;
}
