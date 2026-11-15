#include "battle_15.h"

/* g_BattleChoicePanel byte 0x0B is the panel page base. */

/* func_80096FBC */
MATCH void Battle_SetCommandType(void) {
    u32 flags;
    u8  stage;
    u8  message_slot;

    g_BattleActorTurn->command.type = BATTLE_COMMAND_ABILITY;
    func_80097EC0();
    flags = g_BattleActorTurn->action_flags.value;
    if (flags & COMBATANT_FLAG_DRAGON_FORM) {
        if (!(flags & COMBATANT_FLAG_DRAGON_FORM_CONTROLLED)) {
            g_MenuPanelTasks[16].unk_0B = 2u;
        }
    }
    stage             = g_BattleUIStep;
    message_slot      = g_BattleMessageSlot[5];
    g_Battle.ui_state = 0u;
    g_Battle.ui_step  = (stage + 1u);
    D_80148656        = message_slot;
}
