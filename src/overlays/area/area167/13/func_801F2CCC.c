#include "area167_13.h"

#include "overlays/area/shared/func_801F2C48.h"

MATCH void func_801F2CCC(void) {
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
    cell->pos.x.part.integer   = AREA167_ENTRY_TABLE(u8, 0x18, pair);
    cell->pos.y.part.integer   = AREA167_ENTRY_TABLE(u8, 0x19, pair);
    height                     = Area_HeightSample(cell->pos.x.fixed, cell->pos.y.fixed);
    g_Task->pos.z.part.integer = -height / 2 - AREA167_ENTRY_TABLE(u16, 0x00, pair);
    g_Task->gravity            = AREA167_ENTRY_TABLE(s32, 0x08, entry * 4);
    g_Task->screen_y           = 0;
    g_Task->header.step += 1;
    AREA_ENTRY_CELL_AWAY_STEP(0x80, 1)
    Area_Update();
}
