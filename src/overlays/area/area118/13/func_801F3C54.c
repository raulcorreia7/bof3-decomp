#include "area118_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3C54(void) {
    s32 entry;
    s32 pair;
    s32 height;
    s32 z;
    u8* cell;
    u8  stride;

    entry                      = COORD_INT(g_Task->pos.x);
    g_Task->unk_0A             = 8 - entry;
    g_Task->param.unk_0B       = D_801F5138[COORD_INT(g_Task->pos.y)];
    pair                       = entry * 2;
    g_Task->pos.x.part.integer = D_801F515C[pair];
    g_Task->direction_08       = entry < 1;
    g_Task->pos.y.part.integer = D_801F515D[pair];

    height                     = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    z                          = -height / 2;
    g_Task->pos.z.part.integer = z - D_801F513C[pair];
    g_Task->unk_32             = D_801F513C[pair];
    g_Task->screen_y           = 0;
    g_Task->screen_x           = D_801F514C[pair];

    stride = g_AreaMapBundle.width;
    cell   = g_AreaCellCodes + stride * g_Task->pos.y.part.integer + g_Task->pos.x.part.integer;
    *cell  = 0x52;
    cell   = g_AreaCellCodes + stride * (g_Task->pos.y.part.integer + 1) + g_Task->pos.x.part.integer;
    *cell  = 0x52;
    g_Task->header.step++;

    if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(entry + 1) | COORD_HALF)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(g_Task->pos.y))) <= COORD_HALF || abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(g_Task->pos.y) + 1)) <= COORD_HALF) {
            cell                = g_AreaCellCodes + stride * COORD_INT(g_Task->pos.y) + g_Task->pos.x.part.integer;
            *cell               = 0xA1;
            cell                = g_AreaCellCodes + stride * (COORD_INT(g_Task->pos.y) + 1) + g_Task->pos.x.part.integer;
            *cell               = 0xA1;
            g_Task->screen_y    = -0x100;
            g_Task->header.step = 3;
        }
    }
    func_801F381C(0);
}
#else
INCLUDE_ASM(func_801F3C54);
#endif
