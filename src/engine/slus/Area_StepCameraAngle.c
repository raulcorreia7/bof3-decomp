#include "engine/slus/slus.h"

/* Turns the camera towards an angle in degrees, one step a call, the step count scaled by the route speed; true while steps remain. */
MATCH bool Area_StepCameraAngle(s16 degrees, s8 duration) {
    s32* remaining;
    s32  frames;
    u8   scale;
    u8   speed;

    scale     = 4;
    remaining = &D_801481F4;
    speed     = g_RouteSpeedScale[D_80143FC0];
    if (*remaining == 0) {
        if (speed != 0) {
            if ((D_80143F50 != 2) && (D_80143F50 != 6)) {
                scale = 8;
            }
            scale *= speed;
            frames     = duration * (128 / scale);
            D_801481F0 = g_AreaCameraAngle.vz << 16;
            D_801481F4 = frames;
            D_80148200 = ((((degrees << 12) / 360) - (g_AreaCameraAngle.vz & 0x7FF)) << 16) / frames;
        } else {
            g_AreaCameraAngle.vz = (degrees << 12) / 360;
        }
    } else {
        *remaining -= 1;
        D_801481F0 += D_80148200;
        g_AreaCameraAngle.vz = D_801481F0 >> 16;
    }
    return D_801481F4 != 0;
}
