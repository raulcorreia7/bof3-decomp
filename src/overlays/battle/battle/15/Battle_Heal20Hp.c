#include "battle_15.h"

/* Sets the action target's hp change to -20, a heal of 20. */
/* func_8009DE50 */
MATCH void Battle_Heal20Hp(void) {
    g_Battle.target_record->hp_change = -20;
}
