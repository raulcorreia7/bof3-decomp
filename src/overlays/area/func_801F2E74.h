#include "sys/gameui.h"

/* One definition shared by the ten world04 area request overlays
 * (emi/world04/area176/13 through emi/world04/area185/13) at 0x801F2E74;
 * every change here must verify every member address. */
MATCH void func_801F2E74(void) {
    if (MENU_SELECTION_IDLE()) {
        g_MessageRequest = 0x6F;
        D_801448ED       = 0;
    } else if (g_Zenny >= 500u) {
        g_MessageRequest = 0x7D;
        D_801448ED       = 1;
    } else {
        g_MessageRequest                   = 0x7C;
        g_ScriptWorkRecord->callback_index = 0xFF;
    }
}
