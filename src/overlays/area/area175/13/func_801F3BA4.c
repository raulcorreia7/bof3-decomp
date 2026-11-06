#include "area175_13.h"

MATCH void func_801F3BA4(void) {
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
