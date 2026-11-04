#include "engine/slus/slus.h"

/* records the ground height as the camera height and advances the vertical scroll accumulator
 * by twice its change while the mode flag g_AreaMapBundle.scroll_1E is clear.
 */
/* func_80154FD8 */
MATCH void Area_AdvanceScroll(s16 height) {
    if (g_AreaMapBundle.scroll_1E == 0) {
        g_AreaTileRemainderY -= (height - g_AreaCameraHeight) * 2;
    }
    g_AreaCameraHeight       = height;
    g_AreaCameraRefreshCount = 2;
}
