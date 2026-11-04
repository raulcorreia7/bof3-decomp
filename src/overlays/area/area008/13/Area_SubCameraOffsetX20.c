#include "area008_13.h"

MATCH void Area_SubCameraOffsetX20(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetX      = (u16)g_AreaCameraOffsetX - 0x14;
}
