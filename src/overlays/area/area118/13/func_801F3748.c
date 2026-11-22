#include "area118_13.h"

MATCH void func_801F3748(void) {
    if (SYS_TestFlag(D_80144ED0, TASK(Actor)->param.unk_0B)) {
        (g_AreaCellCodes + COORD_INT(TASK(Actor)->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(TASK(Actor)->pos.x)]                                                       = 0xA1;
        (g_AreaCellCodes +
         (COORD_INT(TASK(Actor)->pos.y) + (TASK(Actor)->direction == FACING_UP_LEFT)) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(TASK(Actor)->pos.x) + TASK(Actor)->direction] = 0xA1;
        TASK(Actor)->header.step                                                                                                                                                          = 1;
    }
    func_801F381C(1);
}
