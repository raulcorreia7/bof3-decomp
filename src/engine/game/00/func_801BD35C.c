#include "game_00.h"

MATCH void func_801BD35C(void) {
    if (!(g_AreaWalkFlags & AREA_WALK_RUN_ACTIVE)) {
        g_Task->header.mode = 1;
    }
}
