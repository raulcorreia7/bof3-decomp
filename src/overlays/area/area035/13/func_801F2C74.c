#include "area035_13.h"

MATCH void func_801F2C74(void) {
    g_CurrentActor->interaction_flags &= ~1;
    Game_SetScriptActive();
    g_ScriptVars[0] = 2;
    D_80146874      = 4;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146875      = 0x14;
}
