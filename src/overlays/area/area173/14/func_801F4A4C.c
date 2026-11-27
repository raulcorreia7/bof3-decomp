#include "area173_14.h"

MATCH void func_801F4A4C(void) {
    Actor*       work;
    PartyMember* current;

    work              = SELF(Actor);
    current           = g_Game.current;
    work->pos.x.fixed = TO_COORD(22) + COORD_HALF;
    work->pos.z.fixed = TO_COORD(1280);
    if (current->chr.character_id == CHAR_ID_GARR) {
        work->pos.y.fixed = TO_COORD(122) + COORD_HALF;
    } else {
        work->pos.y.fixed = TO_COORD(122);
    }
    SELF(Actor)->direction = FACING_UP;
}
