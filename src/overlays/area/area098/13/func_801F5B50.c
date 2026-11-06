#include "area098_13.h"

MATCH void func_801F5B50(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode = 0x2D;
        g_SaveData.scene_event.step = 0;
    }
}
