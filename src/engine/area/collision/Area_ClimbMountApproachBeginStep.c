#include "engine/game/00/game_00.h"

/* func_801B3314 */
/* Mount phase 0: begins the approach, scrolls the area for the leader and moves to phase 1. */
MATCH void Area_ClimbMountApproachBeginStep(void) {
    Area_ClimbMountApproachBegin();
    if ((TASK(Actor)->unk_05 == 0) && ((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE)) == 0) {
        Area_ScrollUpdateWalk();
    }
    TASK(Actor)->unk_03 = 1;
}
