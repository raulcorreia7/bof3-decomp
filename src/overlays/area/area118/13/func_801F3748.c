#include "area118_13.h"

MATCH void func_801F3748(void) {
    if (SYS_TestFlag(D_80144ED0, g_Task->param.unk_0B)) {
        (g_AreaCellCodes + COORD_INT(g_Task->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(g_Task->pos.x)]                                                                     = 0xA1;
        (g_AreaCellCodes + (COORD_INT(g_Task->pos.y) + (g_Task->direction_08 == FACING_UP_LEFT)) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(g_Task->pos.x) + g_Task->direction_08] = 0xA1;
        g_Task->header.step                                                                                                                                                                   = 1;
    }
    func_801F381C(1);
}
