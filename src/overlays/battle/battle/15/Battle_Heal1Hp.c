#include "battle_15.h"

/* Sets the panel task's x half to -1. */
/* func_8009FE70 */
MATCH void Battle_Heal1Hp(void) {
    g_Battle.target_record->hp_change = -1;
}
