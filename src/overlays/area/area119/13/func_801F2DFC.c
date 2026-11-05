#include "area119_13.h"

MATCH void func_801F2DFC(void) {
    u8* row;
    u8* work;
    s32 i;

    i      = 0;
    work   = (u8*)g_Task;
    g_Task = D_80146920;
    row    = D_80146920;
    do {
        FIELD(s32, row, 0x34u) -= 0x400;
        i++;
    } while ((u8)i < 4);
    work[1] = 7;
    g_Task  = work;
    work[9] = 0;
}
