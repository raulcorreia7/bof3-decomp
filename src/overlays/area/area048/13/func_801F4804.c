#include "area048_13.h"

MATCH void func_801F4804(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if (g_CharSlot[g_Game.members[0].chr.character_id] == 1) {
        SYS_ToggleFlag(g_SceneEventFlags, 13);
    }
}
