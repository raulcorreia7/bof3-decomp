#include "engine/game/00/game_00.h"

/* func_801B2950 */
MATCH void Game_LeaderSwitchEnd(void) {
    if (g_AreaCameraMoving == 0) {
        g_AreaWalkFlags &= ~AREA_WALK_LEADER_SWITCH_ACTIVE;
        Area_ScrollAdvance(COORD_INT(g_Task->pos.z));
        g_Task->header.mode = 1;
        ACTOR_CLEAR_STEP();
    }
}
