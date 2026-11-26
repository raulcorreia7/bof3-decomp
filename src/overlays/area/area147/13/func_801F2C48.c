#include "area147_13.h"
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
    cell->pos.x.part.integer = AREA_PAYLOAD_FIELD(D_801F35C0, u8, 0, pair);
    cell->pos.y.part.integer = AREA_PAYLOAD_FIELD(D_801F35C0, u8, 1, pair);
    cell->pos.z.part.integer = AREA_PAYLOAD_FIELD(D_801F35A0, u16, 0, pair);
    cell->screen_x           = AREA_PAYLOAD_FIELD(D_801F35B0, u16, 0, pair);
    cell->unk_32             = AREA_PAYLOAD_FIELD(D_801F35D0, u8, 0, entry);
    cell->header.step += 1;
    cell->screen_y = 0;
    AREA_ENTRY_CELL_AWAY_STEP(128, 1)
    Area_Update(0);
}
