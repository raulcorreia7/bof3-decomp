#include "area098_13.h"

MATCH void func_801F5B50(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x2D;
        g_SceneEventStep = 0;
    }
}
