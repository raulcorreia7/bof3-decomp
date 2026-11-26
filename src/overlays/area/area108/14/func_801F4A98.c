#include "area108_14.h"

MATCH void func_801F4A98(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
    if (g_CharSlot[g_Game.members[0].chr.character_id] == 5) {
        SYS_SetFlag(g_SceneEventFlags, 48U);
        Area_CellSetPalette(1, 11);
        SELF(Actor)->header.flags = 0;
    }
}
