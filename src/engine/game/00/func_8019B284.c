#include "game_00.h"

/* Per-slot column views over the 0x98-byte work records: the trailing padding
 * carries the record stride so each column keeps its own field base. */
/* Column bases: +0x2E, +0x30 and +0x29 of every work record. */

MATCH void func_8019B284(void) {
    Actor* work;
    u8     index;

    work  = SELF(Actor);
    index = work->param.unk_0B;
    if ((work->header.flags & ACTOR_FLAG_HIDDEN) == 0) {
        g_Actors[index].screen_x += work->screen_x;
        g_Actors[index].screen_y += work->screen_y;
        g_Actors[index].draw_layer = work->draw_layer;
    }
    if (!ACTOR_IN_USE(g_Actors[index])) {
        Actor_Clear();
    }
}
