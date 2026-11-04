#include "game_00.h"

MATCH void func_801A253C(Actor* entity) {
    s32    start_x;
    Actor* work;
    u8     mode;
    u8     state;
    u8     flags;

    start_x = g_SpadWork->x.fixed;
    if (g_SpadWork->unk_09 != 0) {
        g_SpadWork->x.fixed = start_x + g_SpadWork->unk_0C;
        g_SpadWork->y.fixed += g_SpadWork->unk_10;
        g_SpadWork->z.part.integer += g_SpadWork->vz;
        g_SpadWork->unk_09--;
        if (g_SpadWork->unk_09 == 0) {
            if (!(entity->flags_74 & 0x80)) {
                g_SpadWork->z.part.integer = Area_SampleHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed);
            }
            work            = g_SpadWork;
            entity->roll_90 = 0;
            mode            = work->state_02;
            if (mode - 1 < 3) {
                entity->timer_75 = (mode & 3) * 0x1E;
                if ((entity->timer_75 & 0xFE) != 0) {
                    func_801A275C(&entity->flags_74);
                    if (!(g_SpadWork->unk_07 & ACTOR_OPT_ROUTE_LOCKED)) {
                        g_SpadWork->direction_08 &= 7;
                        entity->flags_74 |= ACTOR_FLAG_MOVING;
                    }
                    if (!(entity->flags_74 & 0x40)) {
                        state = (g_SpadWork->script_pc < 8) ? 6 : 0;
                    } else {
                        state = 0xFF;
                    }
                    entity->unk_95 = state;
                }
            }
        }
    }
    func_801A3D1C(&entity->flags_74);
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (g_SpadWork->unk_09 <= g_SpadWork->unk_0A) {
            flags = entity->flags_74 | ACTOR_FLAG_SCRIPT_REQUEST;
        } else {
            flags = entity->flags_74 & ~ACTOR_FLAG_SCRIPT_REQUEST;
        }
        entity->flags_74 = flags;
    }
}
