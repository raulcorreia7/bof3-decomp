#include "battle_15.h"

/* func_8009DE18 */
MATCH void Battle_ApplyHeal(void) {
    g_Battle.target_record->hp_change = Battle_CalcHeal(g_Battle.active_battler, g_Battle.target);
}
