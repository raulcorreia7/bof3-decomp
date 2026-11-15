#include "battle_15.h"

/* func_8009F83C */
MATCH void Battle_HalfHpDamage(void) {
    g_Battle.target_record->hp_change = Battle_RollHpDamage(2);
}
