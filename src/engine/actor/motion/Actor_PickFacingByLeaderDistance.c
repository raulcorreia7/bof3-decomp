#include "engine/game/00/game_00.h"

/* func_801A2ED4 */
/* Returns the free facing of the odd or even four that is nearest to, or with the flag farthest from, the leader. */
MATCH u8 Actor_PickFacingByLeaderDistance(Actor* entity, u8 route_step) {
    u32 target_x;
    u32 target_y;
    u8  best;
    u8  i;
    u8  route;
    /* FAKE: retail keeps the x coordinate in a0. */
    FAKE_REG(s32, wx, "a0");
    /* FAKE: retail keeps the y coordinate in v0. */
    FAKE_REG(s32, wy, "v0");
    const s32* px;
    s32*       py;
    s32        dx;
    s32        dy;
    u32        dist;

    target_x = g_Game.members[0].pos.x.fixed + g_Game.members[0].unk_0C * g_Game.members[0].unk_09;
    target_y = g_Game.members[0].pos.y.fixed + g_Game.members[0].unk_10 * g_Game.members[0].unk_09;
    if ((TASK(Actor)->direction & 0x1) == 0) {
        TASK(Actor)->direction++;
    }
    best = 0xFF;
    if ((route_step & BYTE_MASK) == 0u) {
        entity->unk_88 = 0x01000000u;
    } else {
        entity->unk_88 = 0u;
    }
    for (i = 0; i < 4; i++) {
        if ((Actor_IsAheadBlocked(entity) & BYTE_MASK) == 0) {
            route = TASK(Actor)->direction;
            wx    = TASK(Actor)->pos.x.fixed;
            wy    = TASK(Actor)->pos.y.fixed;
            route &= 7;
            px = &g_FacingSteps[route].x;
            py = &g_FacingStepY[route * 2];
            dx = wx + *px;
            dy = wy + *py;
            dx -= target_x;
            dx = ABS(dx);
            dy -= target_y;
            dy   = ABS(dy);
            dist = (dx + dy);
            if ((route_step & BYTE_MASK) != 0u) {
                if (entity->unk_88 < dist) {
                    entity->unk_88 = dist;
                    best           = TASK(Actor)->direction;
                }
            } else if (dist < entity->unk_88) {
                entity->unk_88 = dist;
                best           = TASK(Actor)->direction;
            }
        }
        TASK(Actor)->direction = (TASK(Actor)->direction + 2) & 0x7;
    }
    return best;
}
