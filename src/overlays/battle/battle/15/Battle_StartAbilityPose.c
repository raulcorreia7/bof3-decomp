#include "battle_15.h"

/* func_800A581C */
MATCH void Battle_StartAbilityPose(void) {
    u8* counter;

    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
    g_UIPanelTasks[21].state = 2;
    BATTLE_ACTIVE_MEMBER->u.turn.action_flags.volatile_value |= BATTLER_ACTION_ABILITY_ALT_POSE;
    counter  = (u8*)&g_Battle.ui_mode;
    *counter = *counter + 1;
}
