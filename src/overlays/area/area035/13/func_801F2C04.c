#include "area035_13.h"

MATCH void func_801F2C04(void) {
    ((Actor*)g_CurrentActor)->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    Game_SetScriptActive();
    g_ScriptVars[0] = 1;
    D_80146874      = 4;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146875      = 20;
}
