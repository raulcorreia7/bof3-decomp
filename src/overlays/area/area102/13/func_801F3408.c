#include "area102_13.h"

MATCH void func_801F3408(void) {
    func_801F36B4(g_Task->unk_09);
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 >= 8U) {
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}
