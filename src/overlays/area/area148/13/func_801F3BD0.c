#include "area148_13.h"

MATCH void func_801F3BD0(void) {
    if (MENU_SELECTION_IDLE()) {
        g_UIMessageRequest = MSG_AREA148_NORMAL_MODE_ENGAGED;
        SYS_SetFlag(g_SceneEventFlags, 89);
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
