#include "battle_15.h"

/* func_8009E04C */
MATCH void Battle_CureAilments(void) {
    Battle_CureStatus(g_Battle.target, 0xBFC);
    Battle_MarkDamageApplied();
}
