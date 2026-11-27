#include "area116_13.h"

MATCH s32 func_801F2C04(void) {
    s32  message;
    u32* zenny;

    if (g_UIMessageChoice != 0) {
        message = 4;
    } else {
        zenny = &g_Zenny;
        if (*zenny < 10000u) {
            message = 3;
        } else {
            *zenny -= 10000;
            g_UIMessageRequest = MSG_AREA116_MASTER_ACCEPT_PAYMENT;
            return;
        }
    }
    g_UIMessageRequest = message;
    g_MenuMasterStep   = 6;
}
