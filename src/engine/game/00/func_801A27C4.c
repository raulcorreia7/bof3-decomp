#include "game_00.h"

MATCH void func_801A27C4(Actor* entity) {
    s32 mode;
    u8  saved;
    u8  i;

    mode            = entity->unk_78;
    entity->roll_90 = 0;
    if (mode != 0 && g_SpadWork->unk_01 != 6 && g_SpadWork->unk_01 != 4 && g_SpadWork->unk_03 != 4) {
        func_801A225C((s32)entity, g_RouteSpeedScale[mode], 2);
        saved = g_SpadWork->direction_08;
        for (i = 0; i < 4; i++) {
            g_SpadWork->direction_08 = s_EntityRouteIndices[D_80145E98 & 7][i];
            if ((func_801A1AE4(entity) & BYTE_MASK) != 0) {
                continue;
            }
            if ((g_SpadWork->unk_01 == 3 || g_SpadWork->unk_03 == 3) &&
                (func_801A1A58((Actor*)entity) & BYTE_MASK) == 0) {
                continue;
            }
            break;
        }
        if (i < 4 && g_SpadWork->unk_09 != 0) {
            if (entity->timer_75 != 0) {
                if (g_SpadWork->unk_03 == 4) {
                    g_SpadWork->direction_08 = saved;
                    return;
                }
                entity->timer_75   = 0;
                g_SpadWork->unk_01 = g_SpadWork->unk_03;
            }
            func_801ABBA8(&entity->flags_74, g_SpadWork->direction_08);
            g_SpadWork->direction_08 |= 8;
            if (!(g_SpadWork->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                entity->flags_74 |= ACTOR_FLAG_MOVING;
            }
        } else {
            g_SpadWork->direction_08 = saved & 7;
            g_SpadWork->unk_09       = 0;
        }
    }
}
