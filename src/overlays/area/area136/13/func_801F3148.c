#include "area136_13.h"

MATCH void func_801F3148(void) {
    u16 count_;

    count_                   = g_AreaCameraOffsetY;
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = (u16)(count_ - 2);
}
