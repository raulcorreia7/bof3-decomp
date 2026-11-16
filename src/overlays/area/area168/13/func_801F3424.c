#include "area168_13.h"

#include "overlays/area/func_801F2C48.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3424(void) {
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
    work->direction_08         = work->pos.y.part.integer == 0;
    cell                       = g_Task;
    cell->pos.x.part.integer   = AREA168_ENTRY_TABLE(u8, 0x50, pair);
    cell->pos.y.part.integer   = AREA168_ENTRY_TABLE(u8, 0x51, pair);
    height                     = Area_SampleHeight(cell->pos.x.fixed, cell->pos.y.fixed);
    g_Task->pos.z.part.integer = -height / 2 - AREA168_ENTRY_TABLE(u16, 0x30, pair);
    g_Task->screen_y           = 0;
    g_Task->header.step += 1;
    AREA_ENTRY_CELL_AWAY_STEP(192, 1)
    Area_Update();
}
#else
INCLUDE_ASM(func_801F3424);
#endif
