#include "area132_13.h"

MATCH void func_801F2E38(void) {
    func_801F385C();
    g_Task->timer = 64;
    g_Task->header.step += 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 12));
}
