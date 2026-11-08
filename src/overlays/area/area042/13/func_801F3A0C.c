#include "area042_13.h"

MATCH void func_801F3A0C(void) {
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[COORD_INT(g_Task->pos.x)]) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01));
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}
