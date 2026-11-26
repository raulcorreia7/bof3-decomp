#include "engine/game/00/game_00.h"

/* func_8019C1E4 */
/* Returns whether the cell two steps ahead of the rock blocks it. */
MATCH s32 Actor_RockIsBlockedAhead(void) {
    Actor* work;
    s32    x;
    s32    y;

    work = SELF(Actor);
    x    = work->pos.x.fixed + g_FacingSteps[work->direction].x * 2;
    y    = work->pos.y.fixed + g_FacingSteps[work->direction].y * 2;
    return Actor_RockIsPointBlocked(x, y) & BYTE_MASK;
}
