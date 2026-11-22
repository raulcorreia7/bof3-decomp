#include "area118_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3C54(void) {
    s32 entry;
    s32 pair;
    s32 height;
    s32 z;
    u8* cell;
    u8  stride;

    entry                           = COORD_INT(TASK(Actor)->pos.x);
    TASK(Actor)->unk_0A             = 8 - entry;
    TASK(Actor)->param.unk_0B       = D_801F5138[COORD_INT(TASK(Actor)->pos.y)];
    pair                            = entry * 2;
    TASK(Actor)->pos.x.part.integer = D_801F515C[pair];
    TASK(Actor)->direction          = entry < 1;
    TASK(Actor)->pos.y.part.integer = D_801F515D[pair];

    height                          = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    z                               = -height / 2;
    TASK(Actor)->pos.z.part.integer = z - D_801F513C[pair];
    TASK(Actor)->unk_32             = D_801F513C[pair];
    TASK(Actor)->screen_y           = 0;
    TASK(Actor)->screen_x           = D_801F514C[pair];

    stride = g_AreaMapBundle.width;
    cell   = g_AreaCellCodes + stride * TASK(Actor)->pos.y.part.integer + TASK(Actor)->pos.x.part.integer;
    *cell  = 0x52;
    cell   = g_AreaCellCodes + stride * (TASK(Actor)->pos.y.part.integer + 1) + TASK(Actor)->pos.x.part.integer;
    *cell  = 0x52;
    TASK(Actor)->header.step++;

    if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(entry + 1) | COORD_HALF)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(TASK(Actor)->pos.y))) <= COORD_HALF ||
            abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(TASK(Actor)->pos.y) + 1)) <= COORD_HALF) {
            cell                     = g_AreaCellCodes + stride * COORD_INT(TASK(Actor)->pos.y) + TASK(Actor)->pos.x.part.integer;
            *cell                    = 0xA1;
            cell                     = g_AreaCellCodes + stride * (COORD_INT(TASK(Actor)->pos.y) + 1) + TASK(Actor)->pos.x.part.integer;
            *cell                    = 0xA1;
            TASK(Actor)->screen_y    = -0x100;
            TASK(Actor)->header.step = 3;
        }
    }
    func_801F381C(0);
}
#else
INCLUDE_ASM(func_801F3C54);
#endif
