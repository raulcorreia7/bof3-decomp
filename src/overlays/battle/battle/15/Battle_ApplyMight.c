#include "battle_15.h"

/* func_8009F3DC */
MATCH void Battle_ApplyMight(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_MIGHT;
    func_800A403C(0);
}
