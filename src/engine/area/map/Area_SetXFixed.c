#include "engine/game/00/game_00.h"

/* func_801A253C */
MATCH void Area_SetXFixed(Actor* entity) {
    s32    start_x;
    Actor* work;
    u8     mode;
    u8     state;
    u8     flags;

    start_x = TASK(Actor)->pos.x.fixed;
    if (TASK(Actor)->timer != 0) {
        TASK(Actor)->pos.x.fixed = start_x + TASK(Actor)->vx;
        TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
        COORD_INT(TASK(Actor)->pos.z) += TASK(Actor)->vz;
        TASK(Actor)->timer--;
        if (TASK(Actor)->timer == 0) {
            if (!(entity->interaction_flags & 0x80)) {
                COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
            }
            work            = TASK(Actor);
            entity->roll_90 = 0;
            mode            = work->header.step;
            if (mode - 1 < 3) {
                entity->timer_75 = (mode & 0x3) * 30;
                if ((entity->timer_75 & 0xFE) != 0) {
                    Actor_StartRouteWait(&entity->interaction_flags);
                    if (!(TASK(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                        TASK(Actor)->direction &= 7;
                        entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
                    }
                    if (!(entity->interaction_flags & 0x40)) {
                        state = (TASK(Actor)->script_pc < 8) ? 6 : 0;
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
        if (TASK(Actor)->timer <= TASK(Actor)->unk_0A) {
            flags = entity->interaction_flags | ACTOR_INTERACTION_SCRIPT_REQUEST;
        } else {
            flags = entity->interaction_flags & ~ACTOR_INTERACTION_SCRIPT_REQUEST;
        }
        entity->interaction_flags = flags;
    }
}
