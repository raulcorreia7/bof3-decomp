#include "game_00.h"

MATCH u8 func_8019CAB4(void) {
    Actor* work;
    s8     id;
    u8     walkable;

    work = SELF(Actor);
    id   = Actor_FindInRange(work->pos.x.fixed, work->pos.y.fixed, 0);
    if (id != -1) {
        g_Actors[id].interaction_flags |= ACTOR_INTERACTION_PENDING;
        return 1;
    }
    if (COORD_INT(g_Game.members[0].pos.z) + 64 < Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed)) {
        walkable = 1;
    } else {
        work     = SELF(Actor);
        walkable = (Area_CellGetCode(COORD_INT(work->pos.x), COORD_INT(work->pos.y)) & BYTE_MASK) == 0x11;
    }
    return walkable;
}
