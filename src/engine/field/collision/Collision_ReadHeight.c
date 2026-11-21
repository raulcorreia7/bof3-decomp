#include "engine/slus/slus.h"

/* samples the ground height at the point with the mode's height offset
 * latched, then clears the latch.
 */
MATCH s16 Collision_ReadHeight(s32 x, s32 y) {
    s16 dist;

    Collision_EnableHeightOffset();
    dist                      = Collision_SampleHeight(x, y);
    g_AreaHeightOffsetEnabled = 0;
    return dist;
}
