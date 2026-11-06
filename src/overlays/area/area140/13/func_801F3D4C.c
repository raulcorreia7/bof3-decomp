#include "area140_13.h"

MATCH void func_801F3D4C(void) {
    s32 message;

    if (D_801490C7 == 0) {
        message = 4;
    } else {
        if (D_801490C7 == 1) {
            Game_SetScriptActive();
            g_SceneEventMode = 0x29;
            g_SceneEventStep = 0;
        }
        message = 0xFFFF;
    }
    g_MessageRequest = message;
}
