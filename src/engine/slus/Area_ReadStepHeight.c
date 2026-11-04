#include "engine/slus/slus.h"

/* reads the mode's map value for the point through func_80154ABC and
 * clears the mode's sub-state flag before returning it.
 */
MATCH s16 Area_ReadStepHeight(s32 x, s32 y, u8 mode) {
    s16 dist;

    Area_EnableHeightOffset();
    dist       = func_80154ABC(x, y, mode);
    D_80149340 = 0;
    return dist;
}
