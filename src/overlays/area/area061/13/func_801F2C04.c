#include "area061_13.h"

MATCH s32 func_801F2C04(void) {
    s8 sel;

    sel = D_801490C7;
    if (sel == 0) {
        g_SaveData.zenny = 0;
        g_MessageRequest = 2;
    } else {
        g_MessageRequest = 3;
        g_MasterStep     = 6;
    }
}
