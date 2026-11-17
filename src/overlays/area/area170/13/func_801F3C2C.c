#include "area170_13.h"

#include "overlays/area/func_801F2C48.h"

MATCH void func_801F3C2C(void) {
    Actor* work;
    Actor* cell;
    Actor* row;
    s32    entry;
    s32    pair;
    s16    screen_y;
    s32    height;
    work                       = g_Task;
    entry                      = work->pos.x.part.integer;
    pair                       = entry * 2;
    work->direction            = work->pos.y.part.integer == 0;
    cell                       = g_Task;
    cell->pos.x.part.integer   = AREA_PAYLOAD_FIELD(D_801F57BC, u8, 0xF0, pair);
    cell->pos.y.part.integer   = AREA_PAYLOAD_FIELD(D_801F57BC, u8, 0xF1, pair);
    height                     = Area_SampleHeight(cell->pos.x.fixed, cell->pos.y.fixed);
    g_Task->pos.z.part.integer = -height / 2 - AREA_PAYLOAD_FIELD(D_801F57BC, u16, 0xE4, pair);
    g_Task->screen_y           = 0;
    g_Task->header.step += 1;
    AREA_ENTRY_CELL_AWAY_STEP(192, 1)
    Area_Update();
}
