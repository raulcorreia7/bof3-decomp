#include "area150_13.h"

MATCH void func_801F2CDC(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_ARMED()) {
        g_SceneEventStep = 0xE;
    } else {
        g_SceneEventStep = 0xC;
    }
}
