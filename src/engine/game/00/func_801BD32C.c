#include "game_00.h"

MATCH void func_801BD32C(void) {
    if (!(g_AreaWalkFlags & AREA_WALK_STEP_ACTIVE)) {
        g_Task->header.mode = 1;
    }
}
