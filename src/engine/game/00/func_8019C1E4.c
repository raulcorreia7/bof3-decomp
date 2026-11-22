#include "game_00.h"

MATCH s32 func_8019C1E4(void) {
    Actor* work;
    s32    x;
    s32    y;

    work = TASK(Actor);
    x    = work->pos.x.fixed + g_FacingSteps[work->direction].x * 2;
    y    = work->pos.y.fixed + g_FacingStepY[work->direction * 2] * 2;
    return Area_GetVx(x, y) & BYTE_MASK;
}
