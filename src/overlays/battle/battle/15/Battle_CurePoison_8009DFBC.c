#include "battle_15.h"

/* func_8009DFBC */
MATCH void Battle_CurePoison_8009DFBC(void) {
    Battle_CureStatus(g_Battle.target, 0x80);
    Battle_MarkDamageApplied();
}
