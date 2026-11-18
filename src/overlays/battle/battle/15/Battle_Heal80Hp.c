#include "battle_15.h"

/* Sets the panel task's x half to -80. */
/* func_8009FE84 */
MATCH void Battle_Heal80Hp(void) {
    g_Battle.target_record->hp_change = -80;
}
