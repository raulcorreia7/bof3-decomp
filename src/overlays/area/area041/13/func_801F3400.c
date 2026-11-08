#include "area041_13.h"

MATCH s32 func_801F3400(void) {
    func_801F387C(D_801F4308[g_Task->timer] << 4);
    g_Task->timer += 1;
    if (g_Task->timer >= 0x29U) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x05));
        g_Task->timer            = 0;
        COORD_INT(g_Task->pos.z) = -0x88;
        g_Task->header.step += 1;
    }
}
