#include "area165_13.h"

MATCH void func_801F345C(void) {
    Actor* scratch;
    Actor* check;
    s32    index;
    s32    next_x;
    s32    next_y;
    u8     state;

    scratch               = g_Task;
    scratch->direction_08 = COORD_INT(scratch->y) == 0;
    index                 = COORD_INT(scratch->x) * 2;
    check                 = g_Task;
    next_x                = D_801F35C0[index];
    COORD_INT(check->x)   = next_x;
    next_y                = D_801F35C1[index];
    state                 = check->step;
    COORD_INT(check->z)   = -0x80;
    check->unk_30         = 0x100;
    COORD_INT(check->y)   = next_y;
    check->step           = state + 1;
}
