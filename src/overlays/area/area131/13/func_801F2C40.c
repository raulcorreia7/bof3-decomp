#include "area131_13.h"

MATCH void func_801F2C40(void) {
    if (g_MessageChoice == 0) {
        Game_SetScriptActive();
        D_80146874                              = 7;
        D_80146875                              = 10;
        g_ScriptVars[0]                         = 0;
        ((u8*)g_ScriptWorkRecord)[1]            = 4;
        ((u8*)g_ScriptWorkRecord)[0x78]         = 2;
        ((u8*)g_ScriptWorkRecord)[0x77]         = 4;
        *(u16*)((u8*)g_ScriptWorkRecord + 0x7E) = 0;
        g_MessageRequest                        = 0xC;
    } else {
        g_MessageRequest = MESSAGE_NONE;
    }
}
