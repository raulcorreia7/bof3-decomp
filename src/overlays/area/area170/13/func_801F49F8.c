#include "area170_13.h"

MATCH void func_801F49F8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode = 0x25;
        g_SaveData.scene_event.step = 0x19;
    }
}
