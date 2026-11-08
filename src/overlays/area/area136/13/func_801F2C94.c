#include "area136_13.h"

MATCH void func_801F2C94(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Scene_StartEvent(0x13, 0);
        g_SceneEventSelection = 1;
    }
}
