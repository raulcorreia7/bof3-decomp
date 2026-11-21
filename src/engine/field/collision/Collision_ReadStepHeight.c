#include "engine/slus/slus.h"

/* reads the mode's map value for the point through Collision_GetHeight and
 * clears the mode's sub-state flag before returning it.
 */
MATCH s16 Collision_ReadStepHeight(s32 x, s32 y, u8 mode) {
    s16 dist;

    Collision_EnableHeightOffset();
    dist                      = Collision_GetHeight(x, y, mode);
    g_AreaHeightOffsetEnabled = 0;
    return dist;
}
