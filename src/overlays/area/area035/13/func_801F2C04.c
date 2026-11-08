#include "area035_13.h"

MATCH void func_801F2C04(void) {
    FIELD(u8, g_CurrentActor, 0x74u) &= 0xFE;
    Game_SetScriptActive();
    g_ScriptVars[0] = 1;
    D_80146874      = 4;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146875      = 0x14;
}
