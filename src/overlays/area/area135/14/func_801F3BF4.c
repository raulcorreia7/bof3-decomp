#include "area135_14.h"

MATCH void func_801F3BF4(void) {
    g_AreaSceneMode = 2;
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x2A) == 0) {
        Area_SetCellPalette(0x27, 0x2F);
        SND_PlayCue(EMI_CUE_ID(2, 2));
        g_Task->header.step++;
    }
}
