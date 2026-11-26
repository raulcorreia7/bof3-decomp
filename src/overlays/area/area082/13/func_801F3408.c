#include "area082_13.h"

MATCH void func_801F3408(void) {
    if (g_FrameCount & 1) {
        Area_AddSpark();
    }
    Area_StepSparks();
    if (*g_ScriptVars == 0x29) {
        SELF(Actor)->header.mode++;
    }
}
