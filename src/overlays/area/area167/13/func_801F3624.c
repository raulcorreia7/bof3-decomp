/* Every step re-reads the scratchpad cell. */
#define TASK_VOLATILE
#include "area167_13.h"

MATCH void func_801F3624(void) {
    Actor* work;
    Actor* cell;
    Actor* row;
    s32    entry;
    s32    pair;
    s32    quad;
    s32    z;

    work               = g_Task;
    entry              = work->pos.x.part.integer;
    pair               = entry * 2;
    work->direction_08 = work->pos.y.part.integer == 0;

    cell                     = g_Task;
    cell->pos.x.part.integer = AREA167_ENTRY_TABLE(u8, 0x18, pair);
    cell->pos.y.part.integer = AREA167_ENTRY_TABLE(u8, 0x19, pair);
    z                        = -Area_SampleHeight(cell->pos.x.fixed, cell->pos.y.fixed) / 2 - AREA167_ENTRY_TABLE(u16, 0x00, pair);
    quad                     = entry * 4;
    row                      = g_Task;
    row->pos.z.part.integer  = z;
    row->gravity             = AREA167_ENTRY_TABLE(s32, 0x08, quad);
    row->screen_y            = 0;

    row->header.step += 1;
    Area_Update();
}
