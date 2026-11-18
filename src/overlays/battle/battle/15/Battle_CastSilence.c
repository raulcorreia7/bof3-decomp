#include "battle_15.h"

/* func_8009F5D4 */
MATCH void Battle_CastSilence(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_SILENCE;
    Battle_InflictStatus(0x10);
}
