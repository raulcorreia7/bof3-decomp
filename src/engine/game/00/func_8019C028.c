#include "game_00.h"

MATCH bool func_8019C028(void) {
    s8 slot;
    s8 other;

    slot = Actor_FindInRange(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 0);
    if (slot != -1) {
        g_Actors[slot].interaction_flags |= ACTOR_INTERACTION_PENDING;
    } else {
        other = Game_GetPartySize(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 0);
        if (other == slot) {
            goto fail; /* the other slot is the same slot */
        }
        if (other != 0) {
            g_Game.members[other].header.step = 1;
        }
    }
    TASK(Actor)->header.mode = 4;
    Script_AnimStepLoop();
    Area_SetDrawMode();
    return 1;
fail:
    return 0;
}
