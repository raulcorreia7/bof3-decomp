#include "game_00.h"

MATCH void func_801A2AE4(Actor* entity, u8 route_flag) {
    u8* flag;

    if (g_Task->unk_06 == 0x0A) {
        if (g_Task->timer != 0 && (GAME_WORK_AREA_PTR->interaction_flags & ACTOR_FLAG_MOVING) != 0) {
            func_801A3080(entity, g_Task->direction_08 & 0x7);
            entity->interaction_flags &= ~ACTOR_FLAG_MOVING;
        }
    } else if ((g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED) != 0) {
        entity->interaction_flags &= ~ACTOR_FLAG_MOVING;
    } else {
        entity->interaction_flags |= ACTOR_FLAG_MOVING;
        if (g_Task->timer != 0) {
            g_Task->direction_08 |= 8;
        } else {
            g_Task->direction_08 &= 7;
        }
        flag = &D_1F800003;
        if (*flag != GAME_NONE) {
            if ((route_flag & BYTE_MASK) == g_Task->direction_08) {
                entity->interaction_flags &= ~ACTOR_FLAG_MOVING;
            }
        } else {
            *flag = 0;
        }
    }
}
