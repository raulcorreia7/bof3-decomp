#include "battle_15.h"

/* func_8009DFEC */
MATCH void Battle_CureBlindness(void) {
    Battle_CureStatus(g_Battle.target, 0x8);
    Battle_MarkDamageApplied();
}
