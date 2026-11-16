#include "area061_13.h"

MATCH s32 func_801F2C04(void) {
    s8 sel;

    sel = g_MessageChoice;
    if (sel == 0) {
        g_Zenny          = 0;
        g_MessageRequest = AREA061_MSG_MASTER_AP_TERMS;
    } else {
        g_MessageRequest = AREA061_MSG_MASTER_QUIT;
        g_MenuMasterStep = 6;
    }
}
