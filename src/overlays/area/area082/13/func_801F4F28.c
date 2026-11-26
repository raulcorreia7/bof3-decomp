#include "area082_13.h"

MATCH void func_801F4F28(void) {
    D_8014933A = 0;
    Area_DrawGradient(0x10001805);
    if (g_ScriptVars[0] == 0x35) {
        SELF(Actor)->header.step++;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
    }
}
