#include "area149_13.h"

MATCH void func_801F2CD4(void) {
    s8 value;
    u8 value2;

    value2        = g_Task->timer - 1;
    g_Task->timer = value2;
    if (value2 & BYTE_MASK) {
        g_AreaCameraOffsetZ = g_AreaCameraOffsetZ - 0x2A;
        value               = g_Task->tint.bytes.unk_5D;
        if (value != 0) {
            g_Task->tint.bytes.unk_5D = value - 1;
            g_Task->tint.bytes.unk_5E -= 1;
            g_Task->tint.bytes.unk_5F -= 1;
        }
    } else {
        g_AreaCameraOffsetZ = 0x400;
        g_Task->header.mode = 3;
    }
    g_AreaCameraRefreshCount = 2;
    Area_DrawScreenTint();
}
