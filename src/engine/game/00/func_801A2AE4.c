#include "game_00.h"

MATCH void func_801A2AE4(Actor* entity, u8 route_flag) {
    u8* flag;

    if (g_SpadWork->unk_06 == 0x0A) {
        if (g_SpadWork->unk_09 != 0 && (GAME_WORK_AREA_PTR->flags_74 & ACTOR_FLAG_MOVING) != 0) {
            func_801A3080(entity, g_SpadWork->direction_08 & 7);
            entity->flags_74 &= ~ACTOR_FLAG_MOVING;
        }
    } else if ((g_SpadWork->option_flags & ACTOR_OPT_ROUTE_LOCKED) != 0) {
        entity->flags_74 &= ~ACTOR_FLAG_MOVING;
    } else {
        entity->flags_74 |= ACTOR_FLAG_MOVING;
        if (g_SpadWork->unk_09 != 0) {
            g_SpadWork->direction_08 |= 8;
        } else {
            g_SpadWork->direction_08 &= 7;
        }
        flag = &D_1F800003;
        if (*flag != GAME_NONE) {
            if ((route_flag & BYTE_MASK) == g_SpadWork->direction_08) {
                entity->flags_74 &= ~ACTOR_FLAG_MOVING;
            }
        } else {
            *flag = 0;
        }
    }
}
