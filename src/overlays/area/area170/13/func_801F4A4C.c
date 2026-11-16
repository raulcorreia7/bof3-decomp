#include "area170_13.h"

MATCH void func_801F4A4C(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_ARMED()) {
        g_SceneEventState.step = 0x37;
    } else {
        g_SceneEventState.step = 0x34;
    }
}
