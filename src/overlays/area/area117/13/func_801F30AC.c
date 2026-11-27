#include "area117_13.h"

MATCH void func_801F30AC(void) {
    if (SYS_TestFlag(D_80144ED0, 12) != 0) {
        /* The map bundle's width byte, include/area/area.h. */
        *(g_AreaCellCodes + MEM(u8, MAP_BUNDLE_BASE) * 21 + 1) = 0xA1;
        *(g_AreaCellCodes + MEM(u8, MAP_BUNDLE_BASE) * 22 + 1) = 0xA1;
        SELF(Actor)->header.step                               = 1;
    }
    func_801F314C();
}
