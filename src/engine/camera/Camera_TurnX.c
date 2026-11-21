#include "engine/slus/slus.h"

/* converts a degree target and a degree-per-frame step to the
 * 4096-unit turn the rotation applier works in and hands them to the approach
 * that owns the g_AreaCameraAngle.vx state cell; the returned status is masked to a byte.
 */
MATCH s32 Camera_TurnX(s16 target_degrees, s8 step_degrees) {
    return Camera_StepX(DEG(target_degrees) & ANGLE_MASK, DEG(step_degrees)) & BYTE_MASK;
}
