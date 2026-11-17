#include "game_00.h"

MATCH void func_801A3B7C(Actor* entity) {
    u8  target;
    u8  current;
    s32 sel;

    if (g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED) {
        g_Task->direction = entity->unk_79;
    }

    if (g_Task->unk_0A != 0) {
        g_Task->unk_0A--;
        return;
    }

    target  = entity->unk_79;
    current = g_Task->direction;
    if (target == current) {
        g_Task->header.mode = g_Task->unk_03;
        if (!(g_Task->option_flags & ACTOR_OPT_NO_TARGET)) {
            if ((func_801A1AE4(entity) & BYTE_MASK) != 0u) {
                g_Task->direction &= 7u;
                g_Task->unk_0A = 0u;
                return;
            }
        }
        Area_MoveActorRoute((u8*)entity + 0x74, g_Task->direction);
        g_Task->direction |= 8u;
        entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
        g_Task->unk_0A = g_Task->timer >> 1;
        return;
    }

    sel = -1;
    if (((target - current) & 0x7) < 4) {
        sel = 1;
    }

    g_Task->unk_0A    = 3u;
    current           = g_Task->direction;
    g_Task->vy        = 0;
    g_Task->vx        = 0;
    g_Task->direction = (current + sel) & 0x7u;
    entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
}
