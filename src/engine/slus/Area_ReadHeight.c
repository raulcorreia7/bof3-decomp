#include "engine/slus/slus.h"

/* samples the ground height at the point with the mode's height offset
 * latched, then clears the latch.
 */
MATCH s16 Area_ReadHeight(s32 x, s32 y) {
    s16 dist;

    Area_EnableHeightOffset();
    dist       = Area_SampleHeight(x, y);
    D_80149340 = 0;
    return dist;
}
