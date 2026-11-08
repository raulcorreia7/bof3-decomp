#include "area085_13.h"

MATCH void func_801F2E2C(void) {
    Actor* work;
    u8     step;

    g_Task->header.step++;
    work = g_Task;
    step = work->header.step;
    if (step != 5) {
        work->header.mode = (step & 1) + 1;
    } else {
        g_ScriptVars[0]++;
        /* FAKE: keep the mode assignment after the script update. */
        FAKE_BARRIER();
        work->header.mode = 4;
    }
    Area_DrawScreenTint();
    func_801F2FCC();
}
