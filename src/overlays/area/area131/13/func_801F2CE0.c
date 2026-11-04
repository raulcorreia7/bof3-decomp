#include "area131_13.h"

MATCH void func_801F2CE0(void) {
    MESSAGE_REQUEST_CLEAR();
    if (D_801490C7 == 0) {
        Game_SetScriptActive();
        D_80146874                 = 7;
        g_ScriptVars[0]            = 0;
        D_80146875                 = 0;
        g_ScriptWorkRecord->unk_01 = 4;
        g_ScriptWorkRecord->unk_78 = 2;
        g_ScriptWorkRecord->unk_77 = 2;
        g_ScriptWorkRecord->unk_7E = 0;
    }
}
