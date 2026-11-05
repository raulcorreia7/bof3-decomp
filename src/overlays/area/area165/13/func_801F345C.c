#include "area165_13.h"

MATCH void func_801F345C(void) {
    Actor* scratch;
    Actor* check;
    s32    index;
    s32    next_x;
    s32    next_y;
    u8     state;

    scratch               = g_Task;
    scratch->direction_08 = scratch->y.part.integer == 0;
    index                 = scratch->x.part.integer * 2;
    check                 = g_Task;
    next_x                = D_801F35C0[index];
    check->x.part.integer = next_x;
    next_y                = D_801F35C1[index];
    state                 = check->step;
    check->z.part.integer = -0x80;
    check->unk_30         = 0x100;
    check->y.part.integer = next_y;
    check->step           = state + 1;
}
