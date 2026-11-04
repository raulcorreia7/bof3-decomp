#include "area186_13.h"

MATCH void func_801F2E58(s32 state) {
    s32 mode;

    g_AreaCameraAngle.vx = 256;
    g_AreaCameraOffsetZ  = 0x100;
    g_AreaCameraAngle.vz = 0;
    g_AreaCameraAngle.vy = 0;
    mode                 = 1;
    if ((u8)state == 0) {
        D_80147A8C   = 0x48000;
        g_AreaFocusY = 0xA0000;
        D_80147ACF   = 1;
        mode         = 0;
    } else {
        D_80147A8C   = 0x48000;
        g_AreaFocusY = 0x640000;
        D_80147ACF   = 2;
    }
    func_801C601C(mode);
    D_801448EE = 0x96;
    D_801448EB = 0x27;
    D_801448EC = state;
}
