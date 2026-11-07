#include "area082_13.h"

MATCH void func_801F3C7C(void) {
    g_Task->timer += 1;
    if (g_Task->timer >= 0x11U) {
        g_Task->timer        = 0;
        g_Task->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
    func_801F4430();
}
