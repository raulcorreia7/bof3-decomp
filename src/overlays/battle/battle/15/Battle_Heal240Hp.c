#include "battle_15.h"

/* Sets the panel task's x half to -240. */
/* func_8009FE98 */
MATCH void Battle_Heal240Hp(void) {
    g_Battle.target_record->hp_change = -240;
}
