#include "sys/gameui.h"

/* One definition shared by the ten world04 area request overlays
 * (emi/world04/area176/13 through emi/world04/area185/13) at 0x801F2F50;
 * every change here must verify every member address. */
MATCH void func_801F2F50(void) {
    u16 value;

    if (MENU_SELECTION_ARMED()) {
        value = 0x7B;
    } else if (g_Zenny < 500u) {
        value = 0x7C;
    } else {
        g_MessageRequest = 0x7F;
        D_801F294F       = 0;
        return;
    }
    g_MessageRequest = value;
    D_801F294F       = 1;
}
