#include "area167_13.h"

MATCH void func_801F3CE0(void) {
    s8 variant;

    MESSAGE_REQUEST_CLEAR();
    if (D_801490C7 != 2) {
        variant = 2;
        if (D_801490C7 == 0) {
            variant = 1;
        }
        D_80146866 = variant;
        Game_SetScriptActive();
        D_80146867                  = 0x40;
        g_SaveData.scene_event.mode = 0x20;
        g_SaveData.scene_event.step = 0x15;
    }
}
