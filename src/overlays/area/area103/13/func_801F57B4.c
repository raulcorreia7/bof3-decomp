#include "area103_13.h"

MATCH void func_801F57B4(void) {
    s32 offset = D_801F5D68[g_FrameCount & 0x3];

    g_AreaCameraRefreshCount = 2;
    g_AreaCameraHeight += offset * 8;
}
