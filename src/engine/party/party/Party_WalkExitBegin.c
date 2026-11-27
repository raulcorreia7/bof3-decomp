#include "engine/game/00/game_00.h"

/* func_801B828C */
/* Marks the area entry active and starts the walk animation. */
MATCH void Party_WalkExitBegin(void) {
    g_AreaWalkFlags |= AREA_WALK_ENTRY_ACTIVE;
    Script_Request((SELF(Actor)->direction + 8));
    SELF(Actor)->timer  = 0;
    SELF(Actor)->unk_0A = 0;
    SELF(Actor)->unk_03 = (SELF(Actor)->unk_03 + 1);
}
