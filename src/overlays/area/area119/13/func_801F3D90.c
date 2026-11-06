#include "area119_13.h"

MATCH void func_801F3D90(void) {
    func_801F3F04(g_Task->unk_09);
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 >= 8U) {
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}
