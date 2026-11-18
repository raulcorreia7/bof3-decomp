#include "battle_15.h"

/* func_8009E01C */
MATCH void Battle_CurePetrification(void) {
    Battle_CureStatus(g_Battle.target, 0x100);
    Battle_MarkDamageApplied();
}
