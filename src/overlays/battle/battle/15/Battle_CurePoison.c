#include "battle_15.h"

/* func_8009DD20 */
MATCH void Battle_CurePoison(void) {
    Battle_CureStatus(g_Battle.target, 0x80);
    Battle_MarkDamageApplied();
}
