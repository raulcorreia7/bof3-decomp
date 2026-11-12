#include "area042_13.h"

MATCH void func_801F3DBC(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if ((g_CharSlot[g_Game.members[0].chr.character_id] == 1) && (SYS_TestFlag(g_SceneEventFlags, 11) == 0) && (SYS_TestFlag(g_SceneEventFlags, 17) == 0)) {
        SYS_SetFlag(g_SceneEventFlags, 11U);
        g_SceneEventMode = 7;
        g_SceneEventStep = 0xA;
        D_801448EE       = 0x384;
        g_Game.flags |= 0x20;
    }
}
