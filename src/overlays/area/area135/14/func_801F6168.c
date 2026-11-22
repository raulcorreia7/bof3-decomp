#include "area135_14.h"

MATCH void func_801F6168(s32 value) {
    u16 seed;

    seed = value;
    /* The shift keeps only the low half; the camera seed is that half. */
    if (((value) << 16) != 0) {
        g_AreaCameraSpeed = seed;
    }
    g_AreaScrollTargetX = g_PartyActors[0].pos.x.fixed;
    g_AreaScrollTargetY = g_AreaFocus.y.fixed;
}
