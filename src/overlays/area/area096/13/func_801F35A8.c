#include "area096_13.h"

MATCH void func_801F35A8(void) {
    s32 height;

    height = Area_SampleHeight(D_80145EC4, D_80145EC8);
    if (g_AreaCameraHeight == height) {
        height -= 0x20;
    }
    g_AreaCameraHeight = height;
    MATCH_FAKE_BARRIER(); /* FAKE: keeps the camera store above the refresh-count load */
    g_AreaCameraRefreshCount += 2;
}
