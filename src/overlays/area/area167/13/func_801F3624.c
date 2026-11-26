/* Every step re-reads the scratchpad cell. */
#define FAKE_DECL_SELF_VOLATILE
#include "area167_13.h"

MATCH void func_801F3624(void) {
    Actor* work;
    Actor* cell;
    Actor* actor;
    s32    entry;
    s32    pair;
    s32    quad;
    s32    z;

    work            = SELF(Actor);
    entry           = work->pos.x.part.integer;
    pair            = entry * 2;
    work->direction = work->pos.y.part.integer == 0;

    cell                      = SELF(Actor);
    cell->pos.x.part.integer  = AREA167_ENTRY_TABLE(u8, 0x18, pair);
    cell->pos.y.part.integer  = AREA167_ENTRY_TABLE(u8, 0x19, pair);
    z                         = -Area_HeightSample(cell->pos.x.fixed, cell->pos.y.fixed) / 2 - AREA167_ENTRY_TABLE(u16, 0x00, pair);
    quad                      = entry * 4;
    actor                     = SELF(Actor);
    actor->pos.z.part.integer = z;
    actor->gravity            = AREA167_ENTRY_TABLE(s32, 0x08, quad);
    actor->screen_y           = 0;

    actor->header.step += 1;
    Area_Update();
}
