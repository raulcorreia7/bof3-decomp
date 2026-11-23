#include "engine/slus/slus.h"

/* records the ground height as the camera height and advances the vertical scroll accumulator
 * by twice its change while the mode flag g_AreaMapBundle.scroll is clear.
 */
MATCH void Area_ScrollAdvance(s16 height) {
    if (g_AreaMapBundle.scroll == 0) {
        g_AreaTileRemainderY -= (height - g_AreaCamera.height) * 2;
    }
    g_AreaCamera.height      = height;
    g_AreaCameraRefreshCount = 2;
}
