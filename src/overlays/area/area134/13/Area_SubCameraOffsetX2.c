#include "area134_13.h"

MATCH void Area_SubCameraOffsetX2(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetX      = (u16)g_AreaCameraOffsetX - 2;
}
