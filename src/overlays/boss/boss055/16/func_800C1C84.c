#include "boss055_16.h"

MATCH void func_800C1C84(void) {
    if (g_Battle.action_type != BATTLE_ACTION_ABILITY ||
        (g_Abilities[g_Battle.action_id].targeting_flags & ABILITY_TARGET_NO_HIT_REACT)) {
        func_800C2340(5, 4, 4);
    }
    g_Task->header.step = 1;
}
