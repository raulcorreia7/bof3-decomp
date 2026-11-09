#include "shop_00.h"

MATCH void func_801DE8E8(void) {
    /* Pointer form: retail keeps one base register across the count load and the store. */
    volatile u8* timer = &D_80148654;
    u8           count;

    func_801DF90C();
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        D_80148652 += 1;
    }
}
