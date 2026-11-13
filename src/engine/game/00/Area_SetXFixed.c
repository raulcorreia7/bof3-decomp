#include "game_00.h"

/* func_801A253C */
MATCH void Area_SetXFixed(Actor* entity) {
    s32    start_x;
    Actor* work;
    u8     mode;
    u8     state;
    u8     flags;

    start_x = g_Task->pos.x.fixed;
    if (g_Task->timer != 0) {
        g_Task->pos.x.fixed = start_x + g_Task->vx;
        g_Task->pos.y.fixed += g_Task->vy;
        COORD_INT(g_Task->pos.z) += g_Task->vz;
        g_Task->timer--;
        if (g_Task->timer == 0) {
            if (!(entity->interaction_flags & 0x80)) {
                COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
            }
            work            = g_Task;
            entity->roll_90 = 0;
            mode            = work->header.step;
            if (mode - 1 < 3) {
                entity->timer_75 = (mode & 0x3) * 30;
                if ((entity->timer_75 & 0xFE) != 0) {
                    func_801A275C(&entity->interaction_flags);
                    if (!(g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                        g_Task->direction_08 &= 7;
                        entity->interaction_flags |= ACTOR_FLAG_MOVING;
                    }
                    if (!(entity->interaction_flags & 0x40)) {
                        state = (g_Task->script_pc < 8) ? 6 : 0;
                    } else {
                        state = 0xFF;
                    }
                    entity->unk_95 = state;
                }
            }
        }
    }
    func_801A3D1C(&entity->interaction_flags);
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (g_Task->timer <= g_Task->unk_0A) {
            flags = entity->interaction_flags | ACTOR_FLAG_SCRIPT_REQUEST;
        } else {
            flags = entity->interaction_flags & ~ACTOR_FLAG_SCRIPT_REQUEST;
        }
        entity->interaction_flags = flags;
    }
}
