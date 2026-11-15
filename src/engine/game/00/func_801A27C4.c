#include "game_00.h"

MATCH void func_801A27C4(Actor* entity) {
    s32 mode;
    u8  saved;
    u8  i;

    mode            = entity->unk_78;
    entity->roll_90 = 0;
    if (mode != 0 && g_Task->header.mode != 6 && g_Task->header.mode != 4 && g_Task->unk_03 != 4) {
        func_801A225C(entity, g_RouteSpeedScale[mode], 2);
        saved = g_Task->direction_08;
        for (i = 0; i < 4; i++) {
            g_Task->direction_08 = s_EntityRouteIndices[g_Game.members[0].facing & 0x7][i];
            if ((func_801A1AE4(entity) & BYTE_MASK) != 0) {
                continue;
            }
            if ((g_Task->header.mode == 3 || g_Task->unk_03 == 3) && (func_801A1A58(entity) & BYTE_MASK) == 0) {
                continue;
            }
            break;
        }
        if (i < 4 && g_Task->timer != 0) {
            if (entity->timer_75 != 0) {
                if (g_Task->unk_03 == 4) {
                    g_Task->direction_08 = saved;
                    return;
                }
                entity->timer_75    = 0;
                g_Task->header.mode = g_Task->unk_03;
            }
            Area_MoveActorRoute(&entity->interaction_flags, g_Task->direction_08);
            g_Task->direction_08 |= 8;
            if (!(g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                entity->interaction_flags |= ACTOR_FLAG_MOVING;
            }
        } else {
            g_Task->direction_08 = saved & 0x7;
            g_Task->timer        = 0;
        }
    }
}
