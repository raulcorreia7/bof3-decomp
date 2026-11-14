#include "area169_13.h"

MATCH void func_801F2C48(void) {
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
    cell->pos.x.part.integer = WORLD04_ENTRY_TABLE(D_801F3A90, u8, 0x18, pair);
    cell->pos.y.part.integer = WORLD04_ENTRY_TABLE(D_801F3A90, u8, 0x19, pair);
    cell->pos.z.part.integer = WORLD04_ENTRY_TABLE(D_801F3A90, u16, 0x14, pair);
    cell->screen_y           = 0;
    cell->header.step += 1;
    row = g_Task;
    if (row->direction_08 != 0) {
        if (abs(g_Game.members[0].pos.y.fixed - ((((s32)COORD_INT(row->pos.y) + 1) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.x.fixed - ((s32)COORD_INT(row->pos.x) << 16)) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.x.fixed - (((s32)COORD_INT(row->pos.x) + 1) << 16)) <= TO_COORD(1)) {
                screen_y         = 192;
                row->screen_y    = screen_y;
                row->header.step = 3;
            }
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(row->pos.x) + 1) << 16) | 0x8000)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(row->pos.y) << 16)) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(row->pos.y) + 1) << 16)) <= TO_COORD(1)) {
                screen_y         = 192;
                row->screen_y    = screen_y;
                row->header.step = 3;
            }
        }
    }
    Area_Update();
}
