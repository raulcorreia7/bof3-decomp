#include "area118_13.h"

MATCH void func_801F3748(void) {
    if (SYS_TestFlag(D_80144ED0, SELF(Actor)->param.unk_0B)) {
        (g_AreaCellCodes + COORD_INT(SELF(Actor)->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(SELF(Actor)->pos.x)]                                                       = 0xA1;
        (g_AreaCellCodes +
         (COORD_INT(SELF(Actor)->pos.y) + (SELF(Actor)->direction == FACING_UP_LEFT)) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(SELF(Actor)->pos.x) + SELF(Actor)->direction] = 0xA1;
        SELF(Actor)->header.step                                                                                                                                                          = 1;
    }
    func_801F381C(1);
}
