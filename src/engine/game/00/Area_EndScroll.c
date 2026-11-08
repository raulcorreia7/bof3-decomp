#include "game_00.h"

/* func_801B2950 */
MATCH void Area_EndScroll(void) {
    if (g_AreaCameraMoving == 0) {
        g_AreaWalkFlags &= ~AREA_WALK_LEADER_SWITCH_ACTIVE;
        Area_AdvanceScroll(COORD_INT(g_Task->pos.z));
        g_Task->header.mode = 1;
        ACTOR_CLEAR_STEP();
    }
}
