#include "area135_14.h"

MATCH void func_801F3ED8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode = 0x12;
        g_SaveData.scene_event.step = 0;
    }
}
