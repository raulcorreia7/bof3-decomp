#include "area167_13.h"

#include "overlays/area/shared/func_801F2C48.h"

MATCH void func_801F2CCC(void) {
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
    cell->pos.x.part.integer        = AREA167_ENTRY_TABLE(u8, 0x18, pair);
    cell->pos.y.part.integer        = AREA167_ENTRY_TABLE(u8, 0x19, pair);
    height                          = Area_HeightSample(cell->pos.x.fixed, cell->pos.y.fixed);
    SELF(Actor)->pos.z.part.integer = -height / 2 - AREA167_ENTRY_TABLE(u16, 0x00, pair);
    SELF(Actor)->gravity            = AREA167_ENTRY_TABLE(s32, 0x08, entry * 4);
    SELF(Actor)->screen_y           = 0;
    SELF(Actor)->header.step += 1;
    AREA_ENTRY_CELL_AWAY_STEP(0x80, 1)
    Area_Update();
}
