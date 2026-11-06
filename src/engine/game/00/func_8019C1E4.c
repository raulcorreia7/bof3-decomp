#include "game_00.h"

MATCH s32 func_8019C1E4(void) {
    Actor* work;
    s32    x;
    s32    y;

    work = g_Task;
    x    = work->pos.x.fixed + g_FacingSteps[work->direction_08].x * 2;
    y    = work->pos.y.fixed + D_80181B98[work->direction_08 * 2] * 2;
    return func_8019C344(x, y) & BYTE_MASK;
}
