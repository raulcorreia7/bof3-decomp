#include "area171_13.h"

MATCH void func_801F2CA0(void) {
    Actor* work;
    Actor* cell;
    Actor* row;
    s32    entry;
    s32    pair;
    s16    screen_y;
    s32    height;

    work                     = g_Task;
    entry                    = work->pos.x.part.integer;
    pair                     = entry * 2;
    work->pos.x.part.integer = AREA_PAYLOAD_FIELD(D_801F3F5C, u8, 0x20, pair);
    work->pos.y.part.integer = AREA_PAYLOAD_FIELD(D_801F3F5C, u8, 0x21, pair);
    height                   = Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);
    cell                     = g_Task;
    cell->pos.z.part.integer = -height / 2 - D_801F3F70[entry];
    cell->unk_32             = D_801F3F70[entry];
    cell->vx                 = D_801F3F78[entry] << 24;
    cell->header.step += 1;
    cell->screen_y = 0;

    row = g_Task;
    if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(row->pos.x) + 1) << 16) | 0x8000)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(row->pos.y) << 16)) <= TO_COORD(1) || abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(row->pos.y) + 1) << 16)) <= TO_COORD(1)) {
            screen_y         = 192;
            row->screen_y    = screen_y;
            row->header.step = 3;
        }
    }

    func_801F3070(1);
}
