#include "area136_13.h"

MATCH void func_801F2C3C(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode      = 0x13;
        g_SaveData.scene_event.step      = 0;
        g_SaveData.scene_event.selection = 0;
    }
}
