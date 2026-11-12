#include "area085_13.h"

MATCH void func_801F2E2C(void) {
    u8 step;

    g_Task->header.step++;
    step = g_Task->header.step;
    if (step != 5) {
        g_Task->header.mode = (step & 0x1) + 1;
    } else {
        g_ScriptVars[0]++;
        g_Task->header.mode = 4;
    }
    Area_DrawScreenTint();
    func_801F2FCC();
}
