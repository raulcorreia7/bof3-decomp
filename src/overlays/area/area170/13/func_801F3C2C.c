#include "area170_13.h"

#include "overlays/area/shared/func_801F2C48.h"

MATCH void func_801F3C2C(void) {
    Actor* work;
    Actor* cell;
    Actor* actor;
    s32    entry;
    s32    pair;
    s16    screen_y;
    s32    height;
    work                            = SELF(Actor);
    entry                           = work->pos.x.part.integer;
    pair                            = entry * 2;
    work->direction                 = work->pos.y.part.integer == 0;
    cell                            = SELF(Actor);
    cell->pos.x.part.integer        = AREA_PAYLOAD_FIELD(D_801F57BC, u8, 0xF0, pair);
    cell->pos.y.part.integer        = AREA_PAYLOAD_FIELD(D_801F57BC, u8, 0xF1, pair);
    height                          = Area_HeightSample(cell->pos.x.fixed, cell->pos.y.fixed);
    SELF(Actor)->pos.z.part.integer = -height / 2 - AREA_PAYLOAD_FIELD(D_801F57BC, u16, 0xE4, pair);
    SELF(Actor)->screen_y           = 0;
    SELF(Actor)->header.step += 1;
    AREA_ENTRY_CELL_AWAY_STEP(192, 1)
    Area_Update();
}
