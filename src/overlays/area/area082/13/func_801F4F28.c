#include "area082_13.h"

MATCH void func_801F4F28(void) {
    D_8014933A = 0;
    func_801F5428(0x10001805);
    if (g_ScriptVars[0] == 0x35) {
        g_Task->header.step++;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01));
    }
}
