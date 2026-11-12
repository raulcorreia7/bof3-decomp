#include "area135_14.h"

MATCH void func_801F3BF4(void) {
    g_AreaSceneMode = 2;
    if (SYS_TestFlag(g_SceneEventFlags, 42) == 0) {
        Area_SetCellPalette(39, 47);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
        g_Task->header.step++;
    }
}
