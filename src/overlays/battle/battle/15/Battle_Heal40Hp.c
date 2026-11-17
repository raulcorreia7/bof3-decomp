#include "battle_15.h"

/* Sets the panel task's x half to -40. */
/* func_8009DE64 */
MATCH void Battle_Heal40Hp(void) {
    g_Battle.target_record->hp_change = -40;
}
