#include "area188_13.h"

MATCH void func_801F4618(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Scene_StartEvent(0x2B, 0);
        g_SceneEventSelection = 0;
    }
}
