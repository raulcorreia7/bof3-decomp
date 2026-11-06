#include "area082_13.h"

MATCH void func_801F3D04(void) {
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 >= 0x11U) {
        g_Task->unk_09 = 0;
        g_Task->unk_0B = 2;
        g_Task->header.step += 1;
    }
    func_801F4430();
}
