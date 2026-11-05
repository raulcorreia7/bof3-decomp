#include "area008_13.h"

MATCH void Area_SubCameraOffsetX20(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetX      = g_AreaCameraOffsetX - 0x14;
}
