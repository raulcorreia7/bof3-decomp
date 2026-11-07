#include "area118_13.h"

MATCH void func_801F3FD0(void) {
    if (g_AreaSceneMode != g_Task->unk_0A) {
        if (abs(D_80145EC4 - ((((s32)COORD_INT(g_Task->pos.x) + 1) << 16) | 0x8000)) > TO_COORD(2) ||
            (abs(D_80145EC8 - ((s32)COORD_INT(g_Task->pos.y) << 16)) > TO_COORD(2) &&
             abs(D_80145EC8 - (((s32)COORD_INT(g_Task->pos.y) + 1) << 16)) > TO_COORD(2))) {
            (g_AreaCellCodes +
             COORD_INT(g_Task->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width_00)[COORD_INT(g_Task->pos.x)] = 0x52;
            (g_AreaCellCodes + (COORD_INT(g_Task->pos.y) + 1) *
                                   ((AreaMapBundle*)MAP_BUNDLE_BASE)->width_00)[COORD_INT(g_Task->pos.x)]      = 0x52;
            g_Task->header.step                                                                                = 4;
        }
    }
    func_801F381C(0);
}
