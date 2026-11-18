#include "battle_15.h"

/* Sets the panel task's x half to -5. */
/* func_8009FFE4 */
MATCH void Battle_Heal5Hp(void) {
    g_Battle.target_record->hp_change = -5;
}
