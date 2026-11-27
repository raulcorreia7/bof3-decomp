#include "area143_13.h"

MATCH void func_801F2CB4(void) {
    if (g_ScriptVars[0] == 0xC) {
        SELF(Actor)->header.mode++;
    }
    Area_StepSparkEmitters();
    func_801F2EF0();
}
