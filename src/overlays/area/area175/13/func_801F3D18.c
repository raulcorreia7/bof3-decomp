#include "area175_13.h"

MATCH void func_801F3D18(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
    } else {
        g_MessageRequest                   = 0xF7;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
