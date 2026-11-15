#include "area186_13.h"

MATCH void func_801F2E58(s32 state) {
    s32 mode;

    g_AreaCameraAngle.vx = 256;
    g_AreaCameraOffsetZ  = 0x100;
    g_AreaCameraAngle.vz = 0;
    g_AreaCameraAngle.vy = 0;
    mode                 = 1;
    if ((u8)state == 0) {
        D_80147A8C   = TO_COORD(4) + COORD_HALF;
        g_AreaFocusY = TO_COORD(10);
        D_80147ACF   = 1;
        mode         = 0;
    } else {
        D_80147A8C   = TO_COORD(4) + COORD_HALF;
        g_AreaFocusY = TO_COORD(100);
        D_80147ACF   = 2;
    }
    Area_StartScrollRoute(mode);
    D_801448EE       = 0x96;
    g_SceneEventMode = 0x27;
    g_SceneEventStep = state;
}
