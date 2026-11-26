#include "engine/game/00/game_00.h"

/* The retail code never reads $a0-$a2; the slus caller's arguments are leftover register values kept in its prototype.
*/
/* func_801C24D0 */
MATCH void Area_RunWalk(void) {
    Area_SetWalkVelocity();
    if ((SELF(Actor)->unk_05 == 0) && !((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE))) {
        Area_ScrollUpdateWalk();
    }
}
