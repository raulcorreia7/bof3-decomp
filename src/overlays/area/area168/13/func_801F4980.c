#include "area168_13.h"

MATCH void func_801F4980(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Scene_StartEvent(0x3B, 0xA);
    }
}
