#include "area119_13.h"

MATCH void func_801F2C88(void) {
    u8* actor;
    u8* work;
    s32 i;

    i      = 0;
    work   = SELF(u8);
    g_Self = D_80146920;
    actor  = D_80146920;
    do {
        FIELD(s32, actor, 0x38u) += 0x400;
        i++;
    } while ((u8)i < 4);
    work[1] = 2;
    g_Self  = work;
    work[9] = 4;
}
