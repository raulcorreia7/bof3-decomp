#include "area188_13.h"

MATCH void func_801F4670(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode      = 0x2B;
        g_SaveData.scene_event.step      = 0;
        g_SaveData.scene_event.selection = 1;
    }
}
