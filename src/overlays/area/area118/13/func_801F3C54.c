#include "area118_13.h"

MATCH void func_801F3C54(void) {
    s32 entry;
    s32 pair;
    s32 height;
    s32 z;
    s16 screen_y;

    entry                           = COORD_INT(TASK(Actor)->pos.x);
    TASK(Actor)->unk_0A             = 8 - entry;
    TASK(Actor)->param.unk_0B       = D_801F5138[COORD_INT(TASK(Actor)->pos.y)];
    pair                            = entry * 2;
    TASK(Actor)->pos.x.part.integer = D_801F515C[pair];
    TASK(Actor)->pos.y.part.integer = D_801F515D[pair];
    TASK(Actor)->direction          = entry == 0;

    height                          = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    z                               = -height / 2;
    TASK(Actor)->pos.z.part.integer = z - D_801F513C[entry];
    TASK(Actor)->unk_32             = D_801F513C[entry];
    TASK(Actor)->screen_x           = D_801F514C[entry];
    TASK(Actor)->screen_y           = 0;

    (g_AreaCellCodes + COORD_INT(TASK(Actor)->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(TASK(Actor)->pos.x)]       = 0x52;
    (g_AreaCellCodes + (COORD_INT(TASK(Actor)->pos.y) + 1) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(TASK(Actor)->pos.x)] = 0x52;
    TASK(Actor)->header.step++;

    if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(COORD_INT(TASK(Actor)->pos.x) + 1) | COORD_HALF)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(TASK(Actor)->pos.y))) <= TO_COORD(1) ||
            abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(TASK(Actor)->pos.y) + 1)) <= TO_COORD(1)) {
            (g_AreaCellCodes + COORD_INT(TASK(Actor)->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(TASK(Actor)->pos.x)]       = 0xA1;
            (g_AreaCellCodes + (COORD_INT(TASK(Actor)->pos.y) + 1) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(TASK(Actor)->pos.x)] = 0xA1;
            screen_y                                                                                                                          = -0x100;
            TASK(Actor)->screen_y                                                                                                             = screen_y;
            TASK(Actor)->header.step                                                                                                          = 3;
        }
    }
    func_801F381C(0);
}
