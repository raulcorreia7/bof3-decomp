#include "area112_13.h"

MATCH void func_801F2D18(void) {
    if (SYS_TestFlag(g_SceneEventFlags, COORD_FRAC(g_Task->pos.x))) {
        g_Task->timer            = 0;
        g_Task->header.step      = 1;
        COORD_INT(g_Task->pos.y) = -8;
        func_801F2EA8();
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01));
    }
    func_801F3274();
}
