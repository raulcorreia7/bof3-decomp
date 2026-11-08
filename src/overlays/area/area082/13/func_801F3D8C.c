#include "area082_13.h"

MATCH void func_801F3D8C(void) {
    g_Task->timer++;
    if (g_Task->timer >= 17) {
        g_Task->timer = 0;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01));
        g_Task->header.step++;
    }
    func_801F4430();
}
