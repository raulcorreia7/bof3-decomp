#include "engine/game/00/game_00.h"

/* func_801B7CA0 */
/* Steps off the ladder, then clears the entry flag. */
MATCH void Party_LadderUpExit(void) {
    if ((Area_ClimbDismountExit() & BYTE_MASK) && (TASK(Actor)->unk_05 == 0)) {
        g_AreaWalkFlags &= ~AREA_WALK_ENTRY_ACTIVE;
    }
}
