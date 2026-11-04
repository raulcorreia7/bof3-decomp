#include "area011_13.h"

MATCH void func_801F2C04(void) {
    if ((s16)g_AreaCameraOffsetZ >= -0x13FF) {
        g_AreaCameraOffsetZ = (s16)g_AreaCameraOffsetZ - 0xA0;
    }
    g_AreaCameraRefreshCount = 2;
}
