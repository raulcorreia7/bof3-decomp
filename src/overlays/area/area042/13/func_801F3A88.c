#include "area042_13.h"

MATCH void func_801F3A88(void) {
    func_801F3D18(D_801F534C[g_Task->unk_09 >> 1]);
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 >= 5U) {
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}
