#include "area067_14.h"

MATCH void func_801F451C(void) {
    if (g_Game.members[0].chr.character_id == 6) {
        ((Actor*)g_CurrentActor)->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
        Game_SetScriptActive();
        g_ScriptVars[0] = 0;
        D_80146865      = 0;
        D_80146866      = 0;
        D_80146867      = 0;
        D_80146874      = 4;
        D_80146875      = 0;
    } else {
        ((Actor*)g_CurrentActor)->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    }
}
