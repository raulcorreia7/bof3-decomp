#include "battle_15.h"

/* Sets the panel task's x half to -100. */
/* func_8009DE78 */
MATCH void Battle_Heal100Hp(void) {
    g_Battle.target_record->hp_change = -100;
}
