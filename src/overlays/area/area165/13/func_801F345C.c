#include "area165_13.h"

MATCH void func_801F345C(void) {
    Actor* scratch;
    Actor* check;
    s32    index;
    s32    next_x;
    s32    next_y;
    u8     state;

    scratch                 = g_Task;
    scratch->direction_08   = COORD_INT(scratch->pos.y) == 0;
    index                   = COORD_INT(scratch->pos.x) * 2;
    check                   = g_Task;
    next_x                  = D_801F35C0[index];
    COORD_INT(check->pos.x) = next_x;
    next_y                  = D_801F35C1[index];
    state                   = check->header.step;
    COORD_INT(check->pos.z) = -128;
    check->screen_y         = 256;
    COORD_INT(check->pos.y) = next_y;
    check->header.step      = state + 1;
}
