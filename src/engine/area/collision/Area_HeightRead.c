#include "engine/slus/slus.h"

/* samples the ground height at the point with the mode's height offset
 * latched, then clears the latch.
 */
MATCH s16 Area_HeightRead(s32 x, s32 y) {
    s16 dist;

    Area_HeightEnableOffset();
    dist                      = Area_HeightSample(x, y);
    g_AreaHeightOffsetEnabled = 0;
    return dist;
}
