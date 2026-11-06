#include "area074_13.h"

MATCH s32 func_801F2C04(void) {
    s8  sel;
    s32 request;

    sel = g_MessageChoice;
    if (sel == 0) {
        if (D_80144F94 & 0x20) {
            g_MessageRequest = 0x92;
            return;
        }
        request = 0x93;
    } else {
        request = 0x94;
    }
    g_MessageRequest = request;
    g_MasterStep     = 6;
}
