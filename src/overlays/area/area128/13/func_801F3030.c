/* The direction store re-reads the scratchpad cell. */
#define FAKE_DECL_SELF_VOLATILE
#include "area128_13.h"

MATCH void func_801F3030(void) {
    Actor*       work;
    PartyMember* member;

    work              = SELF(Actor);
    member            = g_Game.current;
    work->pos.x.fixed = TO_COORD_HALF(78);
    work->pos.z.fixed = 0;
    if (member->chr.character_id == CHAR_ID_GARR) {
        work->pos.y.fixed = TO_COORD_HALF(8);
    } else {
        work->pos.y.fixed = TO_COORD(8);
    }
    SELF(Actor)->direction = FACING_UP;
}
