#include "game_00.h"

MATCH bool func_801A3AC8(Actor* record) {
    Actor* rec;
    u8     route;
    s32    x;
    s32    y;
    s32    pos_x;
    s32    pos_y;

    rec   = record;
    route = rec->direction_08 & 0x7;
    pos_x = rec->pos.x.fixed + g_FacingSteps[route].x;
    x     = pos_x;
    pos_y = rec->pos.y.fixed + g_FacingStepY[route * 2];
    y     = pos_y;
    if (func_801BDE14(x, y, g_Task->state_70.byte) == -1) {
        return func_801BE0C0(x, y, g_Task->state_70.byte) != -1;
    }
    return 1;
}
