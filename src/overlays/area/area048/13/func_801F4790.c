#include "area048_13.h"

MATCH void func_801F4790(void) {
    MESSAGE_REQUEST_CLEAR();
    if (!(D_801490C7 & 1)) {
        g_ScriptVars[0] = 0xB;
        SND_PlayCue(0x205);
    } else {
        g_ScriptVars[0] = 1;
        Game_ClearScriptActive();
        D_80146874 = 0;
        D_80146875 = 0;
    }
}
