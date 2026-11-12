#include "area173_14.h"

MATCH void func_801F3570(void) {
    s16* slot;

    slot       = &D_1F800038;
    *slot      = -0x40;
    D_1F80003A = 0;
    func_801F3954(0);
    *slot = 64;
    func_801F3954(1);
    *slot = 0;
    func_801F3954(2);
    g_Task->timer++;
    if (g_Task->timer >= 31) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
        g_Task->timer = 8;
        g_Task->header.step++;
    }
}
