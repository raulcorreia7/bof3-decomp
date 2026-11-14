#include "area174_13.h"

#include "overlays/area/func_801F2C48.h"

MATCH void func_801F3490(void) {
    Actor* work;
    Actor* cell;
    Actor* row;
    s32    entry;
    s32    pair;
    s16    screen_y;
    work                     = g_Task;
    entry                    = work->pos.x.part.integer;
    pair                     = entry * 2;
    work->direction_08       = work->pos.y.part.integer == 0;
    cell                     = g_Task;
    cell->pos.x.part.integer = AREA_PAYLOAD_FIELD(D_801F4FAC, u8, 0x34, pair);
    cell->pos.y.part.integer = AREA_PAYLOAD_FIELD(D_801F4FAC, u8, 0x35, pair);
    cell->pos.z.part.integer = AREA_PAYLOAD_FIELD(D_801F4FAC, u16, 0x24, pair);
    cell->gravity            = AREA_PAYLOAD_FIELD(D_801F4FAC, s32, 0x2C, entry * 4);
    cell->screen_x           = AREA_PAYLOAD_FIELD(D_801F4FAC, u16, 0x28, pair);
    cell->header.step += 1;
    cell->screen_y = 0;
    AREA_ENTRY_CELL_AWAY_STEP(128, 1)
    Area_Update();
}
