#include "engine/game/00/game_00.h"

/* func_801A3B7C */
/* Mode 10: turns the actor one facing at a time toward its target facing, then resumes the saved mode. */
MATCH void Actor_RunTurn(Actor* entity) {
    u8  target;
    u8  current;
    s32 sel;

    if (TASK(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED) {
        TASK(Actor)->direction = entity->unk_79;
    }

    if (TASK(Actor)->unk_0A != 0) {
        TASK(Actor)->unk_0A--;
        return;
    }

    target  = entity->unk_79;
    current = TASK(Actor)->direction;
    if (target == current) {
        TASK(Actor)->header.mode = TASK(Actor)->unk_03;
        if (!(TASK(Actor)->option_flags & ACTOR_OPT_NO_TARGET)) {
            if ((Actor_IsAheadBlocked(entity) & BYTE_MASK) != 0u) {
                TASK(Actor)->direction &= 7u;
                TASK(Actor)->unk_0A = 0u;
                return;
            }
        }
        Area_MoveActorRoute((u8*)entity + 0x74, TASK(Actor)->direction);
        TASK(Actor)->direction |= 8u;
        entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
        TASK(Actor)->unk_0A = TASK(Actor)->timer >> 1;
        return;
    }

    sel = -1;
    if (((target - current) & 0x7) < 4) {
        sel = 1;
    }

    TASK(Actor)->unk_0A    = 3u;
    current                = TASK(Actor)->direction;
    TASK(Actor)->vy        = 0;
    TASK(Actor)->vx        = 0;
    TASK(Actor)->direction = (current + sel) & 0x7u;
    entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
}
