#include "area148_13.h"

#include "overlays/area/func_801F2C48.h"

MATCH void func_801F2CA0(void) {
    Actor* work;
    Actor* cell;
    Actor* row;
    s32    entry;
    s32    pair;
    s16    screen_y;
    work                     = g_Task;
    entry                    = work->pos.x.part.integer;
    pair                     = entry * 2;
    work->direction          = work->pos.y.part.integer == 0;
    cell                     = g_Task;
    cell->pos.x.part.integer = AREA_PAYLOAD_FIELD(D_801F4FC4, u8, 0x40, pair);
    cell->pos.y.part.integer = AREA_PAYLOAD_FIELD(D_801F4FC4, u8, 0x41, pair);
    cell->pos.z.part.integer = AREA_PAYLOAD_FIELD(D_801F4FC4, u16, 0x14, pair);
    cell->gravity            = AREA_PAYLOAD_FIELD(D_801F4FC4, s32, 0x2C, entry * 4);
    cell->screen_x           = AREA_PAYLOAD_FIELD(D_801F4FC4, u16, 0x20, pair);
    cell->unk_32             = AREA_PAYLOAD_FIELD(D_801F4FC4, u8, 0x4C, entry);
    cell->header.step += 1;
    cell->screen_y = 0;
    AREA_ENTRY_CELL_AWAY_STEP(128, 1)
    Area_Update(0);
}
