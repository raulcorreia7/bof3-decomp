#include "engine/slus/slus.h"

/* steps the scene angle g_AreaCameraAngle.vy by step and reports 1 once the masked accumulator has passed target;
 * otherwise it snaps to target and rebuilds D_801481DA from D_801481E2. The two arms spell the comparison with the
 * masked accumulator on the left, which fixes the operand and register order.
 */
MATCH s32 Area_StepCameraY(s16 target, s8 step) {
    s32  value;
    u16* angle;

    if (step != 0) {
        angle  = &g_AreaCameraAngle.vy;
        value  = *angle + step;
        *angle = value;
        if (step > 0) {
            if ((value & ANGLE_MASK) < target) {
                return 1;
            }
        } else {
            if ((value & ANGLE_MASK) > target) {
                return 1;
            }
        }
    }
    g_AreaCameraAngle.vy = target;
    D_801481DA           = target + D_801481E2;
    return 0;
}
