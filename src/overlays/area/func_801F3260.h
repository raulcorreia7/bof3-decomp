#include "sys/gameui.h"

/* One definition shared by the ten world04 area request overlays
 * (emi/world04/area176/13 through emi/world04/area185/13) at 0x801F3260;
 * every change here must verify every member address. */
MATCH void func_801F3260(void) {
    if (MENU_SELECTION_IDLE()) {
        MESSAGE_REQUEST_CLEAR();
        D_801F2944 = 0;
    } else if (D_801490C7 == 1) {
        MESSAGE_REQUEST_CLEAR();
        D_801F2944 = 1;
    } else {
        g_MessageRequest                   = 0x2A1;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
