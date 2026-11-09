#include "area118_13.h"

MATCH void func_801F43FC(void) {
    if (SYS_TestFlag(D_80144ED0, D_801F5198[g_Task->param.unk_0B])) {
        g_Task->timer = 9;
        g_Task->header.step++;
    }
    func_801F4634(0, 64);
}
