#include "area197_13.h"

MATCH void func_801F368C(void) {
    if (SYS_TestFlag(D_80144EF8, 14)) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
    func_801F3768(0x80, 0);
}
