#include "area061_13.h"

MATCH s32 func_801F2C04(void) {
    s8 sel;

    sel = g_UIMessageChoice;
    if (sel == 0) {
        g_Zenny            = 0;
        g_UIMessageRequest = MSG_AREA061_MASTER_OFFER_APPRENTICE;
    } else {
        g_UIMessageRequest = MSG_AREA061_MASTER_ASK_QUIT;
        g_MenuMasterStep   = 6;
    }
}
