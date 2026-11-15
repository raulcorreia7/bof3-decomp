#include "battle_15.h"

/* func_8009F52C */
MATCH void Battle_ApplyWeaken(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_WEAKEN;
    func_800A403C(1);
}
