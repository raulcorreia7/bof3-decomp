#include "area118_13.h"

#include "overlays/area/shared/func_801F2C48.h"

/* Places the gate at its entry cell and height, marks its two cells closed (0x52) or, once its scene flag is set, open (0xA1), and starts the away step when the party stands in it. */
MATCH void func_801F3058(void) {
    Actor* work;
    Actor* cell;
    Actor* gate;
    Actor* row;
    s32    entry;
    s32    pair;
    s16    screen_y;
    s32    height;

    work                       = g_Task;
    work->unk_0A               = work->pos.y.part.integer + 1;
    cell                       = g_Task;
    entry                      = work->pos.x.part.integer;
    cell->param.unk_0B         = D_801F5138[cell->pos.y.part.integer];
    pair                       = entry * 2;
    gate                       = g_Task;
    gate->pos.x.part.integer   = D_801F515C[pair];
    gate->pos.y.part.integer   = D_801F515D[pair];
    gate->direction            = entry == 0;
    height                     = Area_HeightSample(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    g_Task->pos.z.part.integer = -height / 2 - D_801F513C[entry];
    g_Task->unk_32             = D_801F513C[entry];
    g_Task->screen_x           = D_801F514C[entry];
    g_Task->screen_y           = 0;
    if (!SYS_TestFlag(D_80144ED0, g_Task->param.unk_0B)) {
        (g_AreaCellCodes + COORD_INT(g_Task->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(g_Task->pos.x)]                                                               = 0x52;
        (g_AreaCellCodes + (COORD_INT(g_Task->pos.y) + (g_Task->direction == FACING_UP_LEFT)) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(g_Task->pos.x) + g_Task->direction] = 0x52;
        g_Task->header.step                                                                                                                                                             = 5;
    } else {
        (g_AreaCellCodes + COORD_INT(g_Task->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(g_Task->pos.x)]                                                               = 0xA1;
        (g_AreaCellCodes + (COORD_INT(g_Task->pos.y) + (g_Task->direction == FACING_UP_LEFT)) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(g_Task->pos.x) + g_Task->direction] = 0xA1;
        g_Task->header.step++;
        AREA_ENTRY_CELL_AWAY_STEP(-0x100, 1)
    }
    func_801F381C(0);
}
