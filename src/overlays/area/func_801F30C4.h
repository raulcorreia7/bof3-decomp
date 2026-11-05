#include "sys/gameui.h"

/* One definition shared by the ten world04 area request overlays
 * (emi/world04/area176/13 through emi/world04/area185/13) at 0x801F30C4;
 * every change here must verify every member address. */
MATCH void func_801F30C4(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
    } else {
        g_MessageRequest                   = 0xF7;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
