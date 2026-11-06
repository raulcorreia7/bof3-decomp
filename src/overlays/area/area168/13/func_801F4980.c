#include "area168_13.h"

MATCH void func_801F4980(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x3B;
        g_SceneEventStep = 0xA;
    }
}
