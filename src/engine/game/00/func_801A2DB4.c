#include "game_00.h"

MATCH u8 func_801A2DB4(Actor* entity) {
    s32    dx;
    s32    dy;
    u8     status;
    s32    delta;
    u8     route;
    Actor* work;

    work  = g_Task;
    route = work->direction_08;
    delta = D_80145EC4;
    dx    = work->pos.x.fixed - delta;
    dx    = ABS(dx);
    if ((dx >> 0x10) < entity->ext.bounds.half_width) {
        dy    = work->pos.y.fixed;
        delta = D_80145EC8;
        dy -= delta;
        dy = ABS(dy);
        if ((dy >> 0x10) < entity->ext.bounds.half_height) {
            status = func_801A2ED4(entity, 0U);
            if ((status & BYTE_MASK) == GAME_NONE) {
                g_Task->timer = 0;
                return 0xFFU;
            }
            if ((route & 7) != (status & BYTE_MASK)) {
                /* FAKE: basic-block boundary pins handler status. */
                /* FAKE: ORDER_LOCK keeps this statement in place; without it the match is 93.06%. */
                ORDER_LOCK(g_Task->direction_08 = status);
                entity->interaction_flags |= ACTOR_FLAG_MOVING;
            }
            return g_Task->direction_08;
        }
        goto block_11; /* the two records share the exit */
    }
block_11:
    func_801A2C10(entity);
    return func_801A2A04(entity) & BYTE_MASK;
}
