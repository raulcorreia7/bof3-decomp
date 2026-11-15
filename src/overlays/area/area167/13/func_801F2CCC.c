#include "area167_13.h"

#include "overlays/area/func_801F2C48.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2CCC(void) {
    Actor* work;
    Actor* cell;
    Actor* row;
    s32    entry;
    s32    pair;
    s32    quad;
    s32    height;
    s32    z;
    s16    screen_y;

    work                     = g_Task;
    entry                    = work->pos.x.part.integer;
    pair                     = entry * 2;
    work->direction_08       = work->pos.y.part.integer == 0;
    cell                     = g_Task;
    cell->pos.x.part.integer = AREA167_ENTRY_TABLE(u8, 0x18, pair);
    cell->pos.y.part.integer = AREA167_ENTRY_TABLE(u8, 0x19, pair);
    height                   = Area_SampleHeight(cell->pos.x.fixed, cell->pos.y.fixed);
    quad                     = entry * 4;
    z                        = -height / 2 - AREA167_ENTRY_TABLE(u16, 0x00, pair);
    row                      = g_Task;
    row->pos.z.part.integer  = z;
    row->header.step += 1;
    row->gravity  = AREA167_ENTRY_TABLE(s32, 0x08, quad);
    row->screen_y = 0;
    AREA_ENTRY_CELL_AWAY_STEP(0x80, 1)
    Area_Update();
}
#else
INCLUDE_ASM(func_801F2CCC);
#endif
