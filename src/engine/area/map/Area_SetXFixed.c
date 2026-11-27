#include "engine/game/00/game_00.h"

/* func_801A253C */
MATCH void Area_SetXFixed(Actor* entity) {
    s32    start_x;
    Actor* work;
    u8     mode;
    u8     state;
    u8     flags;

    start_x = SELF(Actor)->pos.x.fixed;
    if (SELF(Actor)->timer != 0) {
        SELF(Actor)->pos.x.fixed = start_x + SELF(Actor)->vx;
        SELF(Actor)->pos.y.fixed += SELF(Actor)->vy;
        COORD_INT(SELF(Actor)->pos.z) += SELF(Actor)->vz;
        SELF(Actor)->timer--;
        if (SELF(Actor)->timer == 0) {
            if (!(entity->interaction_flags & 0x80)) {
                COORD_INT(SELF(Actor)->pos.z) = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
            }
            work            = SELF(Actor);
            entity->roll_90 = 0;
            mode            = work->header.step;
            if (mode - 1 < 3) {
                entity->timer_75 = (mode & 0x3) * 30;
                if ((entity->timer_75 & 0xFE) != 0) {
                    Actor_StartRouteWait(&entity->interaction_flags);
                    if (!(SELF(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                        SELF(Actor)->direction &= 7;
                        entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
                    }
                    if (!(entity->interaction_flags & 0x40)) {
                        state = (SELF(Actor)->script_pc < 8) ? 6 : 0;
                    } else {
                        state = 0xFF;
                    }
                    entity->unk_95 = state;
                }
            }
        }
    }
    Actor_TurnRampStep(&entity->interaction_flags);
    if (g_SysThreads[0].tail.game_entry.request != GAME_REQUEST_MESSAGE) {
        if (SELF(Actor)->timer <= SELF(Actor)->unk_0A) {
            flags = entity->interaction_flags | ACTOR_INTERACTION_SCRIPT_REQUEST;
        } else {
            flags = entity->interaction_flags & ~ACTOR_INTERACTION_SCRIPT_REQUEST;
        }
        entity->interaction_flags = flags;
    }
}
