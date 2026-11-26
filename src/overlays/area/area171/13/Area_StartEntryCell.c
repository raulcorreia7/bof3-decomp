#include "area171_13.h"

/* func_801F2CA0 */
MATCH void Area_StartEntryCell(void) {
    Actor* work;
    Actor* cell;
    Actor* actor;
    u16*   point;
    s32    entry;
    s32    pair;
    s32    height;
    s32    z;

    work                     = SELF(Actor);
    entry                    = COORD_INT(work->pos.x);
    pair                     = entry * 2;
    work->pos.x.part.integer = AREA_PAYLOAD_FIELD(D_801F3F5C, u8, 0x20, pair);
    work->pos.y.part.integer = AREA_PAYLOAD_FIELD(D_801F3F5C, u8, 0x21, pair);
    height                   = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);

    z                        = -height / 2;
    point                    = (u16*)&D_801F3F5C[0x14 + pair];
    cell                     = SELF(Actor);
    cell->pos.z.part.integer = z - *point;
    cell->unk_32             = *point;
    cell->vx                 = (s32)(AREA_PAYLOAD_FIELD(D_801F3F5C, u8, 0x1C, entry) << 24);
    cell->header.step += 1;
    cell->screen_y = 0;

    actor = SELF(Actor);
    if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(COORD_INT(actor->pos.x) + 1) | COORD_HALF)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(actor->pos.y))) <= TO_COORD(1) || abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(actor->pos.y) + 1)) <= TO_COORD(1)) {
            actor->screen_y    = 0xC0;
            actor->header.step = 3;
        }
    }

    func_801F3070(1);
}
