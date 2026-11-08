#include "shop_00.h"

MATCH void func_801D352C(void) {
    volatile u8* timer;
    u8           temp;

    timer  = &D_80148654;
    temp   = *timer - 1;
    *timer = temp;
    if (temp == 0) {
        g_MenuStep.step = 1;
    }
}
