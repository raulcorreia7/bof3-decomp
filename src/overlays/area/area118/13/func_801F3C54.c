#include "area118_13.h"

MATCH void func_801F3C54(void) {
    s32 entry;
    s32 pair;
    s32 height;
    s32 z;
    s16 screen_y;

    entry                           = COORD_INT(SELF(Actor)->pos.x);
    SELF(Actor)->unk_0A             = 8 - entry;
    SELF(Actor)->param.unk_0B       = D_801F5138[COORD_INT(SELF(Actor)->pos.y)];
    pair                            = entry * 2;
    SELF(Actor)->pos.x.part.integer = D_801F515C[pair];
    SELF(Actor)->pos.y.part.integer = D_801F515D[pair];
    SELF(Actor)->direction          = entry == 0;

    height                          = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    z                               = -height / 2;
    SELF(Actor)->pos.z.part.integer = z - D_801F513C[entry];
    SELF(Actor)->unk_32             = D_801F513C[entry];
    SELF(Actor)->screen_x           = D_801F514C[entry];
    SELF(Actor)->screen_y           = 0;

    (g_AreaCellCodes + COORD_INT(SELF(Actor)->pos.y) * AREA_MAP_BUNDLE->width)[COORD_INT(SELF(Actor)->pos.x)]       = 0x52;
    (g_AreaCellCodes + (COORD_INT(SELF(Actor)->pos.y) + 1) * AREA_MAP_BUNDLE->width)[COORD_INT(SELF(Actor)->pos.x)] = 0x52;
    SELF(Actor)->header.step++;

    if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(COORD_INT(SELF(Actor)->pos.x) + 1) | COORD_HALF)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(SELF(Actor)->pos.y))) <= TO_COORD(1) ||
            abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(SELF(Actor)->pos.y) + 1)) <= TO_COORD(1)) {
            (g_AreaCellCodes + COORD_INT(SELF(Actor)->pos.y) * AREA_MAP_BUNDLE->width)[COORD_INT(SELF(Actor)->pos.x)]       = 0xA1;
            (g_AreaCellCodes + (COORD_INT(SELF(Actor)->pos.y) + 1) * AREA_MAP_BUNDLE->width)[COORD_INT(SELF(Actor)->pos.x)] = 0xA1;
            screen_y                                                                                                        = -0x100;
            SELF(Actor)->screen_y                                                                                           = screen_y;
            SELF(Actor)->header.step                                                                                        = 3;
        }
    }
    func_801F381C(0);
}
