#include "area171_13.h"

MATCH void func_801F34F8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode      = 0xA;
        g_SaveData.scene_event.step      = 5;
        g_SaveData.scene_event.selection = 0xFF;
    }
}
