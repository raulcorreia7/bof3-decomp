#include "battle_15.h"

MATCH void func_800A0A04(void) {
    Battle_MarkDamageApplied();
    Battle_SetTarget(0xA, 4);
    Battle_RescaleStats(g_Battle.target);
}
