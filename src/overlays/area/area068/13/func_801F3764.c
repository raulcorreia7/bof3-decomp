#include "area068_13.h"

MATCH void func_801F3764(void) {
    u8* p;
    s32 value;
    u16 a;
    u16 b;

    a = D_801F4E08;
    b = D_801F4E04;
    if (b >= a - 1 && b <= a + 1) {
        p          = TASK_BYTES;
        D_801F4E0C = 0;
        value      = 0x15;
    } else {
        p     = TASK_BYTES;
        value = 0x16;
    }
    p[0x1] = value;
}
