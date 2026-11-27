#include "area169_13.h"

#include "overlays/area/shared/func_801F2C48.h"

MATCH void func_801F2C48(void) {
    Actor* work;
    Actor* cell;
    Actor* actor;
    s32    entry;
    s32    pair;
    s16    screen_y;
    work                     = SELF(Actor);
    entry                    = work->pos.x.part.integer;
    pair                     = entry * 2;
    work->direction          = work->pos.y.part.integer == 0;
    cell                     = SELF(Actor);
    cell->pos.x.part.integer = AREA_PAYLOAD_FIELD(D_801F3A90, u8, 0x18, pair);
    cell->pos.y.part.integer = AREA_PAYLOAD_FIELD(D_801F3A90, u8, 0x19, pair);
    cell->pos.z.part.integer = AREA_PAYLOAD_FIELD(D_801F3A90, u16, 0x14, pair);
    cell->screen_y           = 0;
    cell->header.step += 1;
    AREA_ENTRY_CELL_AWAY_STEP(192, 1)
    Area_Update();
}
