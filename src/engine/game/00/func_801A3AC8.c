#include "game_00.h"

MATCH s32 func_801A3AC8(Actor* record) {
    Actor* rec;
    u8     route;
    s32    x;
    s32    y;
    s32    pos_x;
    s32    pos_y;

    rec   = record;
    route = rec->direction_08 & 7;
    pos_x = rec->x.fixed + g_FacingSteps[route].x;
    x     = pos_x;
    pos_y = rec->y.fixed + D_80181B98[route * 2];
    y     = pos_y;
    if (func_801BDE14(x, y, g_SpadWork->state_70.byte) == -1) {
        return func_801BE0C0(x, y, g_SpadWork->state_70.byte) != -1;
    }
    return 1;
}
