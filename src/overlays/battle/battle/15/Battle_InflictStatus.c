#include "battle_15.h"

/* func_800A41D8 */
MATCH u8 Battle_InflictStatus(s32 status_mask) {
    Battle_MarkDamageApplied();
    if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) == 0) {
        Battle_AddStatus(g_Battle.target, status_mask);
        return 0;
    }
    return 1;
}
