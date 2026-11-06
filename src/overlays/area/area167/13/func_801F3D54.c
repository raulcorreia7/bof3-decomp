#include "area167_13.h"

MATCH void func_801F3D54(void) {
    MESSAGE_REQUEST_CLEAR();
    if (D_801490C7 != 2) {
        if (D_801490C7 == 0) {
            D_80146866 = 0;
        } else {
            D_80146866 = 2;
        }
        Game_SetScriptActive();
        D_80146867       = 0x40;
        g_SceneEventMode = 0x20;
        g_SceneEventStep = 0x14;
    }
}
