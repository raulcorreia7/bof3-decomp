#include "battle_15.h"

/* g_BattleChoicePanel byte 0x0B is the panel page base. */

MATCH void func_80096FBC(void) {
    u32 flags;
    u8  stage;
    u8  message_slot;

    g_BattleActorTurn->command.type = BATTLE_COMMAND_ABILITY;
    func_80097EC0();
    flags = g_BattleActorTurn->action_flags.value;
    if (flags & 2) {
        if (!(flags & 0x20000)) {
            D_8014857B = 2u;
        }
    }
    stage           = g_BattleUIStep;
    message_slot    = g_BattleMessageSlot[5];
    g_BattleUIState = 0u;
    g_BattleUIStep  = (stage + 1u);
    D_80148656      = message_slot;
}
