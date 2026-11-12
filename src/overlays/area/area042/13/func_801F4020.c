#include "area042_13.h"

MATCH void func_801F4020(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if ((g_CharSlot[g_Game.members[0].chr.character_id] == 1) && (SYS_TestFlag(g_SceneEventFlags, 20) == 0)) {
        SYS_SetFlag(g_SceneEventFlags, 20U);
        func_801F4188();
        if (SYS_TestFlag(g_SceneEventFlags, 11) == 0) {
            g_CurrentActor->unk_7E += 1;
        }
    }
}
