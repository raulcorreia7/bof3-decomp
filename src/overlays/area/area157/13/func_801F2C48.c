#include "area157_13.h"

#include "overlays/area/shared/func_801F2C48.h"

MATCH void func_801F2C48(void) {
    Actor* work;
    Actor* cell;
    Actor* actor;
    s32    entry;
    s32    pair;
    s16    screen_y;
    work                     = SELF(Actor);
    work->unk_0A             = ((u16)work->pos.y.part.integer >> 1) & 1;
    entry                    = work->pos.x.part.integer;
    pair                     = entry * 2;
    SELF(Actor)->direction   = (SELF(Actor)->pos.y.part.integer ^ 1) & 1;
    cell                     = SELF(Actor);
    cell->pos.x.part.integer = AREA_PAYLOAD_FIELD(D_801F38CC, u8, 0x14, pair);
    cell->pos.y.part.integer = AREA_PAYLOAD_FIELD(D_801F38CC, u8, 0x15, pair);
    cell->pos.z.part.integer = AREA_PAYLOAD_FIELD(D_801F38CC, u16, 0x34, pair);
    cell->screen_y           = 0;
    cell->header.step += 1;
    AREA_ENTRY_CELL_AWAY_STEP(256, 1)
    Area_Update();
}
