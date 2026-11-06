#include "area128_13.h"

MATCH void func_801F2FD8(void) {
    if (D_801490C7 == 0) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode = 0x38;
        g_SaveData.scene_event.step = 0xA;
        g_MessageRequest            = 0x49;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
