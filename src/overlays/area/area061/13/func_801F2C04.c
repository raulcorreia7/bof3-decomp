#include "area061_13.h"

MATCH s32 func_801F2C04(void) {
    s8 sel;

    sel = g_MessageChoice;
    if (sel == 0) {
        g_Zenny          = 0;
        g_MessageRequest = MSG_002;
    } else {
        g_MessageRequest = MSG_003;
        g_MenuMasterStep = 6;
    }
}
