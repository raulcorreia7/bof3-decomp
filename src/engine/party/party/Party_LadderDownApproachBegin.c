#include "engine/game/00/game_00.h"

/* func_801B7D44 */
/* Starts the approach to the ladder top and marks the area entry active. */
MATCH void Party_LadderDownApproachBegin(void) {
    Area_ClimbMountApproachBegin();
    g_AreaWalkFlags |= AREA_WALK_ENTRY_ACTIVE;
    SELF(Actor)->unk_04 = 1;
}
