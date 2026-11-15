#include "area117_13.h"

MATCH void func_801F30AC(void) {
    if (SYS_TestFlag(D_80144ED0, 12) != 0) {
        /* The width byte of the map bundle at 0x80104000, include/area/area.h. */
        *(g_AreaCellCodes + MEM(u8, 0x80104000u) * 21 + 1) = 0xA1;
        *(g_AreaCellCodes + MEM(u8, 0x80104000u) * 22 + 1) = 0xA1;
        g_Task->header.step                                = 1;
    }
    func_801F314C();
}
