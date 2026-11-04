#include "engine/slus/slus.h"

/* advances the 12-bit rotation position g_AreaCameraAngle.vz by the signed step step toward target and reports 1 once
 * it has passed the target; otherwise it snaps to target and rebuilds D_801481DC from D_801481E4 - ANGLE_45.
 */
MATCH s32 Area_StepCameraZ(s16 target, s8 step) {
    s32  value;
    u16* angle;
    s32  coord;

    if (step != 0) {
        angle  = (u16*)&g_AreaCameraAngle.vz;
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
    g_AreaCameraAngle.vz = target;
    coord                = D_801481E4 - ANGLE_45;
    D_801481DC           = target + coord;
    return 0;
}
