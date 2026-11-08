#include "area082_13.h"

MATCH void func_801F51BC(void) {
    D_8014933A = 0;
    func_801F5428(0x10001805);
    g_Task->screen_y -= 6;
    g_Task->unk_32 = (g_Task->unk_32 - (g_Task->vz / 10000)) & 0xFFD;
    func_801F4430();
    g_Task->timer += 1;
    if (g_Task->timer >= 16U) {
        g_Task->header.step += 1;
    }
}
