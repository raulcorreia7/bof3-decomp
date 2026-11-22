#include "area174_13.h"

MATCH void func_801F3378(AreaShot* shot) {
    shot->active     = 1;
    shot->unk_04     = 0;
    shot->pos.x      = TASK(Actor)->pos.x;
    shot->pos.y      = TASK(Actor)->pos.y;
    shot->pos.z      = TASK(Actor)->pos.z;
    shot->velocity.x = (TASK(Actor)->vx - TASK(Actor)->pos.x.fixed) >> 5;
    shot->velocity.y = (TASK(Actor)->vy - TASK(Actor)->pos.y.fixed) >> 5;
    shot->velocity.z = (TASK(Actor)->vz - TASK(Actor)->pos.z.fixed) >> 5;
    shot->unk_08     = 0x40;
    shot->unk_0A     = 0x20;
    shot->timer      = 0x20;
    shot->angle      = func_801F3320(&TASK(Actor)->pos.x.fixed, &TASK(Actor)->vx);
}
