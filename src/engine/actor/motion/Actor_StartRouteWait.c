#include "engine/game/00/game_00.h"

/* func_801A275C */
/* Saves the current mode in unk_03 and switches the actor to the route wait mode. */
MATCH void Actor_StartRouteWait(void* unused) {
    TASK(Actor)->unk_03      = TASK(Actor)->header.mode;
    TASK(Actor)->header.mode = ACTOR_MODE_ROUTE_WAIT;
}
