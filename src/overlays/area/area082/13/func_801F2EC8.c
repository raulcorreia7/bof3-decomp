#include "area082_13.h"

MATCH void func_801F2EC8(void) {
    Actor* work = SELF(Actor);

    work->vy += 8192;
    work->pos.y.fixed += work->vy;
    work->angle_x -= 6;
    if (work->angle_x < 8) {
        work->angle_x = 8;
    }
    SELF(Actor)->angle_y += 6;
    if (--SELF(Actor)->unk_2C == 0) {
        Actor_Clear();
    }
}
