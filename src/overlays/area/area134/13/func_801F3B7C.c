#include "area134_13.h"

MATCH void func_801F3B7C(void) {
    u8* work;
    u8  timer;

    work    = (u8*)g_Task;
    timer   = work[9];
    work[9] = timer + 0xFF;
    if (timer == 0) {
        g_Task->header.mode = 0xF;
    }
}
