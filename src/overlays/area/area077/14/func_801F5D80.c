#include "area077_14.h"

MATCH void func_801F5D80(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = g_AreaCameraOffsetY - 0x14;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
}
