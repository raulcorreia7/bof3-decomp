#include "area074_13.h"

MATCH s32 func_801F2C04(void) {
    s8  sel;
    s32 request;

    sel = g_UiMessageChoice;
    if (sel == 0) {
        if (D_80144F94 & 0x20) {
            g_UiMessageRequest = MSG_AREA074_MASTER_ACCEPT_APPRENTICE;
            return;
        }
        request = MSG_AREA074_MASTER_REFUSE_APPRENTICE;
    } else {
        request = MSG_AREA074_MASTER_FAREWELL;
    }
    g_UiMessageRequest = request;
    g_MenuMasterStep   = 6;
}
