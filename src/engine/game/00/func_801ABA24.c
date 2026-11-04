#include "game_00.h"

MATCH u8 func_801ABA24(void* sub, s32 target, u8 value) {
    u8  action;
    u8  result;
    u32 mode;
    /* FAKE: work pointer pinned to a0, the retail home. */
    MATCH_REG(Actor*, work, "a0");

    action = ((u8*)target)[FIELD(u16, sub, 0xAu)];
    switch (action) {
        case 0x61:
            result = (g_SpadWork->direction_08 & 7) + 0x14;
            break;
        case 0x62:
            result = (g_SpadWork->direction_08 & 7) + 0x1C;
            break;
        case 0x63:
            result = (g_SpadWork->direction_08 & 7) + 0x24;
            break;
        case 0x64:
            result = (g_SpadWork->direction_08 & 7) + 0x2C;
            break;
        case 0x65:
            work   = g_SpadWork;
            mode   = work->direction_08;
            result = (((u32)mode >> 1) & 3) | 0x34;
            /* 0x65 and 0x66 share the route update at set_route. */
            goto set_route;
        case 0x66:
            work   = g_SpadWork;
            mode   = work->direction_08;
            result = (((u32)mode >> 1) & 3) | 0x10;
        set_route:
            mode &= 6;
            mode += 1;
            work->direction_08 = mode;
            break;
        case 0x60:
        default:
            result = g_SpadWork->direction_08 & 7;
            break;
    }
    FIELD(u8, sub, 0x0u) |= 0x40;
    g_SpadWork->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    Actor_SelectScript(result);
    return g_SpadWork->direction_08;
}
