#include "game_00.h"

MATCH void func_801A2AE4(Actor* entity, u8 route_flag) {
    u8* flag;

    if (SELF(Actor)->unk_06 == 0x0A) {
        if (SELF(Actor)->timer != 0 && (GAME_WORK_AREA_PTR->interaction_flags & ACTOR_INTERACTION_MOVING) != 0) {
            func_801A3080(entity, SELF(Actor)->direction & 0x7);
            entity->interaction_flags &= ~ACTOR_INTERACTION_MOVING;
        }
    } else if ((SELF(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED) != 0) {
        entity->interaction_flags &= ~ACTOR_INTERACTION_MOVING;
    } else {
        entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
        if (SELF(Actor)->timer != 0) {
            SELF(Actor)->direction |= 8;
        } else {
            SELF(Actor)->direction &= 7;
        }
        flag = &g_ScratchPad.cells.bytes[3];
        if (*flag != GAME_NONE) {
            if ((route_flag & BYTE_MASK) == SELF(Actor)->direction) {
                entity->interaction_flags &= ~ACTOR_INTERACTION_MOVING;
            }
        } else {
            *flag = 0;
        }
    }
}
