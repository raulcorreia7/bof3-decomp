#include "area167_13.h"

MATCH void func_801F3EB4(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_ScriptVars[3]             = 0x60;
        g_SaveData.scene_event.mode = 0x20;
        g_SaveData.scene_event.step = 0xA;
    }
}
