#include "area116_13.h"

MATCH void func_801F2C04(void) {
    s32  message;
    u32* zenny;

    if (D_801490C7 != 0) {
        message = 4;
    } else {
        zenny = &g_Zenny;
        if (*zenny < 10000u) {
            message = 3;
        } else {
            *zenny -= 10000;
            g_MessageRequest = 2;
            return;
        }
    }
    g_MessageRequest = message;
    g_MasterStep     = 6;
}
