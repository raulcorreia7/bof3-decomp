#include "area008_13.h"

MATCH void Area_AddCameraOffsetX20(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetX      = (u16)g_AreaCameraOffsetX + 0x14;
}
