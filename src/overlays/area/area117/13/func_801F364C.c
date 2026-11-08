#include "area117_13.h"

MATCH void func_801F364C(void) {
    if (SYS_TestFlag(D_80144ED0, D_801F463C[g_Task->param.unk_0B])) {
        g_Task->timer       = 9;
        g_Task->header.step++;
    }
    func_801F3884(0, 0x40);
}
