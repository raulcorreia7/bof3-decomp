#include "engine/game/00/game_00.h"

/* func_801B35EC */
/* Dismount phase 2: begins the exit, scrolls the area for the leader and moves to phase 3. */
MATCH void Area_ClimbDismountExitBeginStep(void) {
    if (Area_ClimbDismountExitBegin() & BYTE_MASK) {
        if ((TASK(Actor)->unk_05 == 0) && ((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE)) == 0) {
            Area_ScrollUpdateWalk();
        }
        TASK(Actor)->unk_03 = 3;
    }
}
