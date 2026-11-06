#include "area150_13.h"

MATCH void func_801F2CDC(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_ARMED()) {
        g_SaveData.scene_event.step = 0xE;
    } else {
        g_SaveData.scene_event.step = 0xC;
    }
}
