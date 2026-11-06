#include "area167_13.h"

MATCH void func_801F3CE0(void) {
    s8 variant;

    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice != 2) {
        variant = 2;
        if (g_MessageChoice == 0) {
            variant = 1;
        }
        D_80146866 = variant;
        Game_SetScriptActive();
        D_80146867       = 0x40;
        g_SceneEventMode = 0x20;
        g_SceneEventStep = 0x15;
    }
}
