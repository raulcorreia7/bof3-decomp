#include "battle_15.h"

/* func_80096FBC */
MATCH void Battle_SetCommandType(void) {
    u32 flags;
    u8  stage;
    u8  message_slot;

    g_BattleActorTurn->command.type = BATTLE_COMMAND_ABILITY;
    Battle_InitAbilityPanel();
    flags = g_BattleActorTurn->action_flags.value;
    if (flags & BATTLER_ACTION_DRAGON_FORM) {
        if (!(flags & BATTLER_ACTION_DRAGON_FORM_CONTROLLED)) {
            g_BattleChoicePanel.abilities.ability_type = 2u;
        }
    }
    stage            = g_BattleUIStep;
    message_slot     = g_BattleMessageSlot[5];
    g_Battle.ui_mode = 0u;
    g_Battle.ui_step = (stage + 1u);
    D_80148656       = message_slot;
}
