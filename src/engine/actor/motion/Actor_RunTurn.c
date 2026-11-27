#include "engine/game/00/game_00.h"

/* func_801A3B7C */
/* Mode 10: turns the actor one facing at a time toward its target facing, then resumes the saved mode. */
MATCH void Actor_RunTurn(Actor* entity) {
    u8  target;
    u8  current;
    s32 sel;

    if (SELF(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED) {
        SELF(Actor)->direction = entity->unk_79;
    }

    if (SELF(Actor)->unk_0A != 0) {
        SELF(Actor)->unk_0A--;
        return;
    }

    target  = entity->unk_79;
    current = SELF(Actor)->direction;
    if (target == current) {
        SELF(Actor)->header.mode = SELF(Actor)->unk_03;
        if (!(SELF(Actor)->option_flags & ACTOR_OPT_NO_TARGET)) {
            if ((Actor_IsAheadBlocked(entity) & BYTE_MASK) != 0u) {
                SELF(Actor)->direction &= 7u;
                SELF(Actor)->unk_0A = 0u;
                return;
            }
        }
        Area_MoveActorRoute((u8*)entity + 0x74, SELF(Actor)->direction);
        SELF(Actor)->direction |= 8u;
        entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
        SELF(Actor)->unk_0A = SELF(Actor)->timer >> 1;
        return;
    }

    sel = -1;
    if (((target - current) & 0x7) < 4) {
        sel = 1;
    }

    SELF(Actor)->unk_0A    = 3u;
    current                = SELF(Actor)->direction;
    SELF(Actor)->vy        = 0;
    SELF(Actor)->vx        = 0;
    SELF(Actor)->direction = (current + sel) & 0x7u;
    entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
}
