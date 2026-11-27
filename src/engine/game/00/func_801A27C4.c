#include "game_00.h"

MATCH void func_801A27C4(Actor* entity) {
    s32 mode;
    u8  saved;
    u8  i;

    mode            = entity->unk_78;
    entity->roll_90 = 0;
    if (mode != 0 && SELF(Actor)->header.mode != 6 && SELF(Actor)->header.mode != 4 && SELF(Actor)->unk_03 != 4) {
        Actor_PaceFree(entity, g_RouteSpeedScale[mode], 2);
        saved = SELF(Actor)->direction;
        for (i = 0; i < 4; i++) {
            SELF(Actor)->direction = s_EntityRouteIndices[g_Game.members[0].facing & 0x7][i];
            if ((Actor_IsAheadBlocked(entity) & BYTE_MASK) != 0) {
                continue;
            }
            if ((SELF(Actor)->header.mode == 3 || SELF(Actor)->unk_03 == 3) && (Actor_IsAheadInHomeBox(entity) & BYTE_MASK) == 0) {
                continue;
            }
            break;
        }
        if (i < 4 && SELF(Actor)->timer != 0) {
            if (entity->timer_75 != 0) {
                if (SELF(Actor)->unk_03 == 4) {
                    SELF(Actor)->direction = saved;
                    return;
                }
                entity->timer_75         = 0;
                SELF(Actor)->header.mode = SELF(Actor)->unk_03;
            }
            Area_MoveActorRoute(&entity->interaction_flags, SELF(Actor)->direction);
            SELF(Actor)->direction |= 8;
            if (!(SELF(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
            }
        } else {
            SELF(Actor)->direction = saved & 0x7;
            SELF(Actor)->timer     = 0;
        }
    }
}
