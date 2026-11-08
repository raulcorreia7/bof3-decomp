#include "area119_13.h"

MATCH void func_801F3D4C(void) {
    g_Task->timer = 0;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
    g_Task->header.step++;
}
