#include "area074_13.h"

MATCH s32 func_801F2C04(void) {
    s8  sel;
    s32 request;

    sel = g_MessageChoice;
    if (sel == 0) {
        if (D_80144F94 & 0x20) {
            g_MessageRequest = AREA074_MSG_MASTER_ACCEPTS;
            return;
        }
        request = AREA074_MSG_MASTER_REFUSES;
    } else {
        request = AREA074_MSG_MASTER_FAREWELL;
    }
    g_MessageRequest = request;
    g_MenuMasterStep = 6;
}
