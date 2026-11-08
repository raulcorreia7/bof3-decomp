#include "area082_13.h"

MATCH void func_801F50C4(void) {
    D_8014933A = 0;
    func_801F5428(-1);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
    g_Task->timer = 0;
    g_Task->header.step++;
}
