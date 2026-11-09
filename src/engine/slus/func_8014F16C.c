#include "engine/slus/slus.h"

/* arms the fade timer and mode byte. */
MATCH void func_8014F16C(void) {
    g_AreaCameraOffsetZ      = 0x5DC;
    g_AreaCameraRefreshCount = 2;
    GFX_RunBlackFade(-0x800, 1, 0);
}
