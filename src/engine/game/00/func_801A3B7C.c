#include "game_00.h"

MATCH void func_801A3B7C(Actor* entity) {
    u8  target;
    u8  current;
    s32 sel;

    if (g_SpadWork->option_flags & ACTOR_OPT_ROUTE_LOCKED) {
        g_SpadWork->direction_08 = entity->unk_79;
    }

    if (g_SpadWork->unk_0A != 0) {
        g_SpadWork->unk_0A--;
        return;
    }

    target  = entity->unk_79;
    current = g_SpadWork->direction_08;
    if (target == current) {
        g_SpadWork->unk_01 = g_SpadWork->unk_03;
        if (!(g_SpadWork->option_flags & ACTOR_OPT_NO_TARGET)) {
            if ((func_801A1AE4(entity) & BYTE_MASK) != 0u) {
                g_SpadWork->direction_08 &= 7u;
                g_SpadWork->unk_0A = 0u;
                return;
            }
        }
        func_801ABBA8((u8*)entity + 0x74, g_SpadWork->direction_08);
        g_SpadWork->direction_08 |= 8u;
        entity->flags_74 |= ACTOR_FLAG_MOVING;
        g_SpadWork->unk_0A = g_SpadWork->unk_09 >> 1;
        return;
    }

    sel = -1;
    if (((target - current) & 7) < 4) {
        sel = 1;
    }

    g_SpadWork->unk_0A       = 3u;
    current                  = g_SpadWork->direction_08;
    ((s32*)g_SpadWork)[4]    = 0;
    ((s32*)g_SpadWork)[3]    = 0;
    g_SpadWork->direction_08 = (current + sel) & 7u;
    entity->flags_74 |= ACTOR_FLAG_MOVING;
}
