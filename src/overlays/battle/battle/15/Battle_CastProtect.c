#include "battle_15.h"

/* func_8009F4F4 */
MATCH void Battle_CastProtect(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_PROTECT;
    func_800A403C(1);
}
