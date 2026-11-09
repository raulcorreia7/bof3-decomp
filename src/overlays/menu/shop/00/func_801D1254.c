#include "shop_00.h"

MATCH void func_801D1254(void) {
    /* Pointer form: retail keeps one base register across the count load and the store. */
    volatile u8* p   = &D_80148654;
    u8           val = *p - 1;

    *p = val;
    if (val == 0) {
        D_801E606C       = 0;
        D_801E603C       = 0;
        D_801E6040       = 0;
        *p               = 0;
        D_80148655       = 0;
        g_MenuStep.state = 0;
        g_MenuStep.sub_step += 1;
    }
}
