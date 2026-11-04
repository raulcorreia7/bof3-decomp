#include "engine/slus/slus.h"

/* arms the fade timer and mode byte, then calls GFX_RunBlackFade with delta
 * -0x800, semi-transparency 1 and order 0.
 */
MATCH void func_8014F16C(void) {
    g_AreaCameraOffsetZ      = 0x5DC;
    g_AreaCameraRefreshCount = 2;
    GFX_RunBlackFade(-0x800, 1, 0);
}
