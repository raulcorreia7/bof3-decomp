#include "area139_13.h"

MATCH void func_801F2FF0(void) {
    if (g_GameCellType == 2 && !SYS_TestFlag(g_SceneEventFlags, 92)) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 0x06));
        g_Task->header.mode = 0;
    }
    if (g_GameCellType == 3 && SYS_TestFlag(g_SceneEventFlags, 93)) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 0x06));
        g_Task->header.mode = 0;
    }
}
