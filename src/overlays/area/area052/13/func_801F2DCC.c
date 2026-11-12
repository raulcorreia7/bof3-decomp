#include "area052_13.h"

MATCH void func_801F2DCC(void) {
    if (g_Task->timer == 0) {
        func_801F3084();
    }
    g_Task->timer += 1;
    if (g_Task->timer == 4) {
        g_Task->timer = 0;
        g_Task->unk_06 += 1;
    }
    Area_UpdateEffectRows();
    if (g_Task->unk_06 == g_Task->param.unk_0B) {
        g_Task->header.mode += 1;
    }
}
