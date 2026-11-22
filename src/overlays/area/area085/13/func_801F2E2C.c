#include "area085_13.h"

MATCH void func_801F2E2C(void) {
    u8 step;

    TASK(Actor)->header.step++;
    step = TASK(Actor)->header.step;
    if (step != 5) {
        TASK(Actor)->header.mode = (step & 0x1) + 1;
    } else {
        g_ScriptVars[0]++;
        TASK(Actor)->header.mode = 4;
    }
    Area_DrawScreenTint();
    func_801F2FCC();
}
