#include "game_00.h"

MATCH bool func_801A1AE4(Actor* arg) {
    u8  route;
    s32 pos_x;
    s32 pos_y;
    s32 x;
    s32 y;

    route = arg->direction_08 & 0x7;
    pos_x = arg->pos.x.fixed + g_FacingSteps[route].x;
    x     = pos_x;
    pos_y = arg->pos.y.fixed + g_FacingStepY[route * 2];
    y     = pos_y;

    if ((func_801A1BC0(arg) & BYTE_MASK) != 0u) {
        return 1;
    }

    if (func_801BDE14(pos_x, pos_y, g_Task->state_70.byte) == -1) {
        return func_801BE0C0(x, y, g_Task->state_70.byte) != -1;
    }

    return 1;
}
