#include "game_00.h"

MATCH bool func_801A1A58(Actor* actor) {
    /* FAKE: entity base in a2. */
    FAKE_REG(Actor*, entity, "a2");
    /* FAKE: x delta in v0. */
    FAKE_REG(s32, dx, "v0");
    s32 dy_sum;
    /* FAKE: retail resolves the y delta in v1. */
    FAKE_REG(s32, dy_delta, "v1");
    s32 bound_x;
    s32 bound_y;
    u8  route;

    entity = actor;
    route  = entity->direction_08;
    /* FAKE: retail loads the route byte before the coordinate loads. */
    FAKE_BARRIER();
    dx = entity->pos.x.fixed;
    dx += g_FacingSteps[(route & 0x7)].x;
    dy_sum = entity->pos.y.fixed;
    dy_sum += g_FacingStepY[(route & 0x7) * 2];
    dx = (dx >> 16) - FIELD(s16, entity, 0x82u);
    /* FAKE: retail loads the x bound after the delta. */
    FAKE_BARRIER();
    bound_x = entity->ext.bounds.half_width;
    dx      = ABS(dx);
    /* The comparison result reuses bound_x's register in retail. */
    bound_x = (bound_x < dx);
    if (bound_x != 0) {
        return 0;
    }
    dy_delta = (dy_sum >> 16) - FIELD(s16, entity, 0x86u);
    bound_y  = entity->ext.bounds.half_height;
    if (dy_delta < 0) {
        dy_delta = -dy_delta;
    }
    return bound_y >= dy_delta;
}
