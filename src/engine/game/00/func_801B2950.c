#include "game_00.h"

MATCH void func_801B2950(void) {
    if (g_AreaCameraMoving == 0) {
        g_AreaWalkFlags &= ~AREA_WALK_STEP_ACTIVE;
        Area_AdvanceScroll(g_Task->z.part.integer);
        g_Task->mode = 1;
        ACTOR_CLEAR_STATE();
    }
}
