#include "game_00.h"

MATCH void func_801990D0(void) {
    s16* pos_x;
    u16* mirror_x;
    s16* pos_y;
    u16* mirror_y;
    s16  cur;
    s16  clamp;
    u16  mirror_x_value;
    /* FAKE: pin the mirror halfword to v1 so the address keeps v0, as retail. */
    FAKE_REG(u16, mirror_y_value, "v1");

    pos_x = &g_AreaCameraAngle.vx;
    cur   = *pos_x;
    if (cur >= -0x2A9) {
        mirror_x       = &D_801481D8;
        mirror_x_value = *mirror_x;
        *pos_x         = cur - AREA_CAMERA_STEP;
        *mirror_x      = mirror_x_value - AREA_CAMERA_STEP;
    } else {
        clamp      = -682;
        *pos_x     = clamp;
        D_801481D8 = clamp;
    }
    pos_y = &g_AreaCameraAngle.vz;
    cur   = *pos_y;
    if (cur != ANGLE_45) {
        if (D_80143BB1 == 0) {
            if (cur >= ANGLE_45 + 1) {
                mirror_y       = &D_801481DC;
                mirror_y_value = *mirror_y;
                cur -= AREA_CAMERA_STEP;
                *pos_y    = cur;
                *mirror_y = mirror_y_value - AREA_CAMERA_STEP;
                return;
            }
        } else if (cur < ANGLE_45) {
            mirror_y       = &D_801481DC;
            mirror_y_value = *mirror_y;
            cur += AREA_CAMERA_STEP;
            *pos_y    = cur;
            *mirror_y = mirror_y_value + AREA_CAMERA_STEP;
            return;
        }
        *pos_y     = ANGLE_45;
        D_801481DC = ANGLE_45;
    }
}
