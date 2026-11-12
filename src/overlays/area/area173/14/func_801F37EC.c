#include "area173_14.h"

MATCH void func_801F37EC(void) {
    s16* slot;

    if (g_AreaSceneMode == 2) {
        SYS_ClearFlag(g_SceneEventFlags, 129);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
        slot       = &D_1F800038;
        *slot      = -0x180;
        D_1F80003A = 0;
        func_801F3954(0);
        *slot = 384;
        func_801F3954(1);
        *slot      = 0;
        D_1F80003A = 0x180;
        func_801F3954(2);
        g_Task->timer = 96;
        g_Task->header.step++;
    }
}
