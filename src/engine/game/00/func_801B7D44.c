#include "game_00.h"

MATCH void func_801B7D44(void) {
    Area_ClimbMountApproachBegin();
    g_AreaWalkFlags |= AREA_WALK_ENTRY_ACTIVE;
    TASK(Actor)->unk_04 = 1;
}
