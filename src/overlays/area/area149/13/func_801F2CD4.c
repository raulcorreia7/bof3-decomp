#include "area149_13.h"

MATCH void func_801F2CD4(void) {
    s8 value;
    u8 value2;

    ACTOR_COUNT_DOWN(value2, timer);
    if (value2 & BYTE_MASK) {
        g_AreaCameraOffsetZ = g_AreaCameraOffsetZ - 0x2A;
        value               = g_Task->tint.bytes.rgb.r;
        if (value != 0) {
            g_Task->tint.bytes.rgb.r = value - 1;
            g_Task->tint.bytes.rgb.g -= 1;
            g_Task->tint.bytes.rgb.b -= 1;
        }
    } else {
        g_AreaCameraOffsetZ = 0x400;
        g_Task->header.mode = 3;
    }
    g_AreaCameraRefreshCount = 2;
    Area_DrawScreenTint();
}
