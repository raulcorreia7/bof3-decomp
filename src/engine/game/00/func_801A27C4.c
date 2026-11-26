#include "game_00.h"

MATCH void func_801A27C4(Actor* entity) {
    s32 mode;
    u8  saved;
    u8  i;

    mode            = entity->unk_78;
    entity->roll_90 = 0;
    if (mode != 0 && TASK(Actor)->header.mode != 6 && TASK(Actor)->header.mode != 4 && TASK(Actor)->unk_03 != 4) {
        Actor_PaceFree(entity, g_RouteSpeedScale[mode], 2);
        saved = TASK(Actor)->direction;
        for (i = 0; i < 4; i++) {
            TASK(Actor)->direction = s_EntityRouteIndices[g_Game.members[0].facing & 0x7][i];
            if ((Actor_IsAheadBlocked(entity) & BYTE_MASK) != 0) {
                continue;
            }
            if ((TASK(Actor)->header.mode == 3 || TASK(Actor)->unk_03 == 3) && (Actor_IsAheadInHomeBox(entity) & BYTE_MASK) == 0) {
                continue;
            }
            break;
        }
        if (i < 4 && TASK(Actor)->timer != 0) {
            if (entity->timer_75 != 0) {
                if (TASK(Actor)->unk_03 == 4) {
                    TASK(Actor)->direction = saved;
                    return;
                }
                entity->timer_75         = 0;
                TASK(Actor)->header.mode = TASK(Actor)->unk_03;
            }
            Area_MoveActorRoute(&entity->interaction_flags, TASK(Actor)->direction);
            TASK(Actor)->direction |= 8;
            if (!(TASK(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
            }
        } else {
            TASK(Actor)->direction = saved & 0x7;
            TASK(Actor)->timer     = 0;
        }
    }
}
