#include "area082_13.h"

MATCH void func_801F5124(void) {
    D_8014933A = 0;
    func_801F5428(0x10001805);
    g_Task->unk_32 = (g_Task->unk_32 - g_Task->vz / 10000) & 0xFFD;
    func_801F4430();
    if (*g_ScriptVars == 0x3A) {
        g_Task->step++;
    }
}
