#include "engine/game/00/game_00.h"

/* func_801B828C */
/* Marks the area entry active and starts the walk animation. */
MATCH void Party_WalkExitBegin(void) {
    g_AreaWalkFlags |= AREA_WALK_ENTRY_ACTIVE;
    Script_Request((TASK(Actor)->direction + 8));
    TASK(Actor)->timer  = 0;
    TASK(Actor)->unk_0A = 0;
    TASK(Actor)->unk_03 = (TASK(Actor)->unk_03 + 1);
}
