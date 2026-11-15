#include "battle_15.h"

/* func_8009F814 */
MATCH void Battle_FullHpDamage(void) {
    g_Battle.target_record->hp_change = Battle_RollHpDamage(1);
}
