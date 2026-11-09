#include "area118_13.h"

MATCH void func_801F4340(void) {
    g_Task->timer--;
    if (g_Task->timer == 0) {
        g_Task->header.step++;
    }
    func_801F4634(0, 0x40);
    func_801F4634(g_Task->param.unk_0B + SYS_TestFlag(D_80144ED0, D_801F5138[g_Task->param.unk_0B]) * 4 + 1, g_Task->timer << 3);
    func_801F48E0();
}
