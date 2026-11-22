#include "game_00.h"

MATCH void func_801A2AE4(Actor* entity, u8 route_flag) {
    u8* flag;

    if (TASK(Actor)->unk_06 == 0x0A) {
        if (TASK(Actor)->timer != 0 && (GAME_WORK_AREA_PTR->interaction_flags & ACTOR_INTERACTION_MOVING) != 0) {
            func_801A3080(entity, TASK(Actor)->direction & 0x7);
            entity->interaction_flags &= ~ACTOR_INTERACTION_MOVING;
        }
    } else if ((TASK(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED) != 0) {
        entity->interaction_flags &= ~ACTOR_INTERACTION_MOVING;
    } else {
        entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
        if (TASK(Actor)->timer != 0) {
            TASK(Actor)->direction |= 8;
        } else {
            TASK(Actor)->direction &= 7;
        }
        flag = &D_1F800003;
        if (*flag != GAME_NONE) {
            if ((route_flag & BYTE_MASK) == TASK(Actor)->direction) {
                entity->interaction_flags &= ~ACTOR_INTERACTION_MOVING;
            }
        } else {
            *flag = 0;
        }
    }
}
