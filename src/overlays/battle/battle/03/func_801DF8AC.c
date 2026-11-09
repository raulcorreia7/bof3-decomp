#include "battle_03.h"

/* selects the next local-state handler from one of two tables and calls it immediately. */

MATCH void func_801DF8AC(void) {
    PartyMember* battle_work = g_Game.current;
    Callback     handler;

    if ((battle_work->u.turn.action_flags.volatile_value & COMBATANT_FLAG_DRAGON_FORM_QUEUED) != 0u) {
        handler = D_801EB188[0];
    } else {
        handler = D_801EB15C[BATTLE_LOCAL_BYTE_79(battle_work)];
    }

    handler();
}
