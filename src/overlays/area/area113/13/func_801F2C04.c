#include "area113_13.h"

MATCH s32 func_801F2C04(void) {
    u16 request;

    if (MENU_SELECTION_ARMED()) {
        request = 4;
    } else if (D_801454EC < 6) {
        request = 3;
    } else {
        request          = 2;
        g_MessageRequest = request;
        return;
    }
    g_MessageRequest = request;
    g_MenuMasterStep = 6;
}
