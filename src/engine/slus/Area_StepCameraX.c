#include "engine/slus/slus.h"

/* advances the 12-bit rotation position g_AreaCameraAngle.vx by the signed step step toward target and reports 1 once it has passed the target. */
MATCH u8 Area_StepCameraX(s16 target, s8 step) {
    s32  value;
    u16* angle;
    s32  coord;

    if (step != 0) {
        angle  = &g_AreaCameraAngle.vx;
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
    g_AreaCameraAngle.vx = target;
    coord                = D_801481E0 + 682;
    D_801481D8.vx        = target + coord;
    return 0;
}
