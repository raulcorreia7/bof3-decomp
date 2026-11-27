#include "area085_13.h"

MATCH void func_801F2E2C(void) {
    u8 step;

    SELF(Actor)->header.step++;
    step = SELF(Actor)->header.step;
    if (step != 5) {
        SELF(Actor)->header.mode = (step & 0x1) + 1;
    } else {
        g_ScriptVars[0]++;
        SELF(Actor)->header.mode = 4;
    }
    Area_DrawScreenTint();
    func_801F2FCC();
}
