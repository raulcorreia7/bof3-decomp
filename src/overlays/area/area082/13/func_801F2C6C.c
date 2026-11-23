#include "area082_13.h"

MATCH void func_801F2C6C(void) {
    Actor* actor;

    actor              = TASK(Actor);
    actor->unk_2C      = 0x20;
    actor->angle_x     = 0;
    actor->angle_y     = 0;
    actor->angle_z     = 0;
    actor->header.mode = actor->header.mode + 1;
}
