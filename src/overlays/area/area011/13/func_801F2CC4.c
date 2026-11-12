#include "area011_13.h"

MATCH void func_801F2CC4(void) {
    u32* p;

    if (SYS_TestFlag(D_80144EF8, 19) == 0) {
        return;
    }
    if (SYS_TestFlag(D_80144EF8, 20) != 0) {
        return;
    }
    p = (u32*)(0x80104000 + (MEM(u16, 0x80104022) << 2));
    if (*p == 0) {
        return;
    }
    while (*p != 0) {
        u32 v = *p;
        if ((v & 0xFF000000) == 0x81000000) {
            p += 2;
            p[1] = 0x21080000;
            p[0] = 0x21080000;
            return;
        }
        p = (u32*)((u8*)p + ((v >> 14) & 0x3FC));
    }
}
