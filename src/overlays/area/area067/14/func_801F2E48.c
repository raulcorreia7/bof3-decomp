#include "area067_14.h"

MATCH void func_801F2E48(void) {
    u16* rect = (u16*)&g_Task->vx;

    g_Task->timer = 90;
    rect[2]       = 0;
    rect[3]       = 0;
    g_Task->header.mode++;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 1));
}
