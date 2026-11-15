#include "battle_15.h"

/* func_8009F7EC */
MATCH void Battle_ThirdHpDamage(void) {
    g_Battle.target_record->hp_change = Battle_RollHpDamage(3);
}
