#include "area082_13.h"

MATCH void func_801F3408(void) {
    if (g_FrameCount & 1) {
        Area_AddSpark();
    }
    func_801F3AAC();
    if (*g_ScriptVars == 0x29) {
        g_Task->header.mode++;
    }
}
