#include "area008_13.h"

MATCH void Area_SubViewOffsetX20(void) {
    g_AreaViewRefreshCount = 2;
    g_AreaViewOffsetX      = (u16)g_AreaViewOffsetX - 0x14;
}
