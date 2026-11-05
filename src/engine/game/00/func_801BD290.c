#include "game_00.h"

MATCH void func_801BD290(s32 pos_x, s32 pos_y, s8* direction_out) {
    Actor* work;
    s32    dx;
    s32    dy;
    s8     direction;

    work = g_Task;
    dx   = pos_x - work->x.fixed;
    dy   = pos_y - work->y.fixed;
    if (dx < 0 && dy < 0) {
        *direction_out = 0;
        return;
    }
    if (dx > 0 && dy > 0) {
        direction = 4;
    } else if (dx < 0 && dy > 0) {
        direction = 6;
    } else if (dx > 0 && dy < 0) {
        direction = 2;
    } else if (dx > 0 && dy == 0) {
        direction = 3;
    } else if (dx < 0 && dy == 0) {
        direction = 7;
    } else if (dx == 0 && dy > 0) {
        direction = 5;
    } else if (dx == 0 && dy < 0) {
        direction = 1;
    } else {
        return;
    }
    *direction_out = direction;
}
