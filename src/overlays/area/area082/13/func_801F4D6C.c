#include "area082_13.h"

MATCH void func_801F4D6C(void) {
    if (g_ScriptVars[0] == 0x32) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x08));
        g_Task->timer = 0;
        g_Task->header.step++;
    }
}
