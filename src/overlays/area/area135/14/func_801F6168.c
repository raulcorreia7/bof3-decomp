#include "area135_14.h"

MATCH void func_801F6168(s32 value) {
    u16 seed;

    seed = value;
    /* The shift keeps only the low half; the camera seed is that half. */
    if (((value) << 16) != 0) {
        g_AreaCameraStep = seed;
    }
    g_AreaScrollTargetX = D_80147A8C;
    g_AreaScrollTargetY = g_AreaFocusY;
}
