#include "area050_13.h"

MATCH s32 func_801F2C04(void) {
    u16 request;

    if (MENU_SELECTION_ARMED()) {
        request = 0x84;
    } else if (D_801454F3 < 0x1E) {
        request = 0x83;
    } else {
        request            = 0x82;
        g_UiMessageRequest = request;
        return;
    }
    g_UiMessageRequest = request;
    g_MenuMasterStep   = 6;
}
