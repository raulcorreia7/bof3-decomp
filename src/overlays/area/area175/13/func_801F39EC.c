#include "area175_13.h"

MATCH void func_801F39EC(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = 0x7A;
    } else {
        g_MessageRequest                   = 0x6E;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
