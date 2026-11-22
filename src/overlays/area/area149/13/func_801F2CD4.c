#include "area149_13.h"

MATCH void func_801F2CD4(void) {
    s8 value;
    u8 value2;

    ACTOR_COUNT_DOWN(TASK(Actor), value2, timer);
    if (value2 & BYTE_MASK) {
        g_AreaCameraOffsetZ = g_AreaCameraOffsetZ - 0x2A;
        value               = TASK(Actor)->tint.bytes.rgb.r;
        if (value != 0) {
            TASK(Actor)->tint.bytes.rgb.r = value - 1;
            TASK(Actor)->tint.bytes.rgb.g -= 1;
            TASK(Actor)->tint.bytes.rgb.b -= 1;
        }
    } else {
        g_AreaCameraOffsetZ      = 0x400;
        TASK(Actor)->header.mode = 3;
    }
    g_AreaCameraRefreshCount = 2;
    Area_DrawScreenTint();
}
