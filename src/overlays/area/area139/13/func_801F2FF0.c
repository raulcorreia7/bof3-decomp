#include "area139_13.h"

MATCH void func_801F2FF0(void) {
    if (D_80143F03 == 2 && !SYS_TestFlag(g_SceneEventFlags, 92)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x06));
        g_Task->header.mode = 0;
    }
    if (D_80143F03 == 3 && SYS_TestFlag(g_SceneEventFlags, 93)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x06));
        g_Task->header.mode = 0;
    }
}
