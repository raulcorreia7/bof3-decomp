#include "area103_13.h"

MATCH void func_801F44B0(void) {
    if (g_Task->unk_09 % 5 == 0) {
        func_801F4E70(g_Task->unk_09 / 5 + 4);
    }
    g_Task->unk_09++;
    if (g_Task->unk_09 / 5 == 3) {
        g_Task->header.step++;
        g_Task->unk_09 = 1;
    }
}
