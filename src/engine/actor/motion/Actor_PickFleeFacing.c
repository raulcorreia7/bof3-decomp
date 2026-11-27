#include "engine/game/00/game_00.h"

/* func_801A2C94 */
/* Picks the free facing farthest from the leader while the leader is inside the actor's box, else a random one. */
MATCH u8 Actor_PickFleeFacing(Actor* actor) {
    s32    dx;
    s32    dy;
    Actor* entity;
    u8     status;
    s32    delta;
    u8     route;
    Actor* work;

    entity = actor;
    work   = SELF(Actor);
    route  = work->direction;
    delta  = work->pos.x.fixed;
    dx     = g_Game.members[0].pos.x.fixed - delta;
    dx     = ABS(dx);
    if ((dx >> 0x10) < entity->ext.bounds.half_width) {
        dy    = g_Game.members[0].pos.y.fixed;
        delta = work->pos.y.fixed;
        dy -= delta;
        dy = ABS(dy);
        if ((dy >> 0x10) < entity->ext.bounds.half_height) {
            status = Actor_PickFacingByLeaderDistance(entity, 1U);
            if ((status & BYTE_MASK) == GAME_NONE) {
                SELF(Actor)->timer = 0;
                return 0xFFU;
            }
            if ((route & 0x7) != (status & BYTE_MASK)) {
                /* FAKE: basic-block boundary pins handler status. */
                /* FAKE: FAKE_ORDER_LOCK keeps this statement in place; without it the match is 93.06%. */
                FAKE_ORDER_LOCK(SELF(Actor)->direction = status);
                entity->interaction_flags |= ACTOR_INTERACTION_MOVING;
            }
            return SELF(Actor)->direction;
        }
        goto block_11; /* the two records share the exit */
    }
block_11:
    Actor_TurnRandom(entity);
    return Actor_FindFreeFacing(entity) & BYTE_MASK;
}
