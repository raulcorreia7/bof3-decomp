#include "game_00.h"

MATCH s32 func_8019C028(void) {
    s8 slot;
    s8 other;

    slot = func_801BDE14(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0);
    if (slot != -1) {
        g_Actors[slot].interaction_flags |= ACTOR_FLAG_INTERACTION_PENDING;
    } else {
        other = func_801BE0C0(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0);
        if (other == slot) {
            goto fail; /* the other slot is the same slot */
        }
        if (other != 0) {
            g_Game.members[other].header.step = 1;
        }
    }
    g_Task->header.mode = 4;
    func_8014D978();
    Area_SetDrawMode();
    return 1;
fail:
    return 0;
}
