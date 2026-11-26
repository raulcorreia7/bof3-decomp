#include "engine/game/00/game_00.h"

/* func_8019C028 */
/* Returns true when an actor or party member stands at the rock: flags it and ends the rock. */
MATCH bool Actor_RockHit(void) {
    s8 slot;
    s8 other;

    slot = Actor_FindInRange(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 0);
    if (slot != -1) {
        g_Actors[slot].interaction_flags |= ACTOR_INTERACTION_PENDING;
    } else {
        other = Game_GetPartySize(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 0);
        if (other == slot) {
            goto fail; /* the other slot is the same slot */
        }
        if (other != 0) {
            g_Game.members[other].header.step = 1;
        }
    }
    SELF(Actor)->header.mode = ACTOR_ROCK_MODE_END;
    Script_AnimStepLoop();
    Area_SetDrawMode();
    return 1;
fail:
    return 0;
}
