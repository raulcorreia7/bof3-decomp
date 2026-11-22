#include "game_00.h"

MATCH void func_801B828C(void) {
    g_AreaWalkFlags |= AREA_WALK_ENTRY_ACTIVE;
    Script_Request((TASK(Actor)->direction + 8));
    TASK(Actor)->timer  = 0;
    TASK(Actor)->unk_0A = 0;
    TASK(Actor)->unk_03 = (TASK(Actor)->unk_03 + 1);
}
