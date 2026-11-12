#include "game_00.h"

#define WORK g_Task

MATCH u8 func_801A2ED4(Actor* entity, u8 route_step) {
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
    if ((WORK->direction_08 & 0x1) == 0) {
        WORK->direction_08++;
    }
    best = 0xFF;
    if ((route_step & BYTE_MASK) == 0u) {
        entity->unk_88 = 0x01000000u;
    } else {
        entity->unk_88 = 0u;
    }
    for (i = 0; i < 4; i++) {
        if ((func_801A1AE4(entity) & BYTE_MASK) == 0) {
            route = WORK->direction_08;
            wx    = WORK->pos.x.fixed;
            wy    = WORK->pos.y.fixed;
            route &= 7;
            px = &g_FacingSteps[route].x;
            py = &g_FacingStepY[route * 2];
            dx = wx + *px;
            dy = wy + *py;
            /* FAKE: retail forms the y sum before the x subtraction. */
            FAKE_USE(dy);
            dx -= target_x;
            dx = ABS(dx);
            dy -= target_y;
            dy   = ABS(dy);
            dist = (dx + dy);
            if ((route_step & BYTE_MASK) != 0u) {
                if (entity->unk_88 < dist) {
                    entity->unk_88 = dist;
                    best           = WORK->direction_08;
                }
            } else if (dist < entity->unk_88) {
                entity->unk_88 = dist;
                best           = WORK->direction_08;
            }
        }
        WORK->direction_08 = (WORK->direction_08 + 2) & 0x7;
    }
    return best;
}
