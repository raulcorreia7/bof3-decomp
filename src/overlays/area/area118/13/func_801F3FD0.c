#include "area118_13.h"

MATCH void func_801F3FD0(void) {
    if (g_AreaSceneMode != SELF(Actor)->unk_0A) {
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(SELF(Actor)->pos.x) + 1) << 16) | 0x8000)) > TO_COORD(2) ||
            (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(SELF(Actor)->pos.y) << 16)) > TO_COORD(2) &&
             abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(SELF(Actor)->pos.y) + 1) << 16)) > TO_COORD(2))) {
            (g_AreaCellCodes + COORD_INT(SELF(Actor)->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(SELF(Actor)->pos.x)]       = 0x52;
            (g_AreaCellCodes + (COORD_INT(SELF(Actor)->pos.y) + 1) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(SELF(Actor)->pos.x)] = 0x52;
            SELF(Actor)->header.step                                                                                                          = 4;
        }
    }
    func_801F381C(0);
}
