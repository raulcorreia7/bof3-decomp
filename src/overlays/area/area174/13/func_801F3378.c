#include "area174_13.h"

MATCH void func_801F3378(AreaShot* shot) {
    shot->active     = 1;
    shot->unk_04     = 0;
    shot->pos.x      = SELF(Actor)->pos.x;
    shot->pos.y      = SELF(Actor)->pos.y;
    shot->pos.z      = SELF(Actor)->pos.z;
    shot->velocity.x = (SELF(Actor)->vx - SELF(Actor)->pos.x.fixed) >> 5;
    shot->velocity.y = (SELF(Actor)->vy - SELF(Actor)->pos.y.fixed) >> 5;
    shot->velocity.z = (SELF(Actor)->vz - SELF(Actor)->pos.z.fixed) >> 5;
    shot->unk_08     = 0x40;
    shot->unk_0A     = 0x20;
    shot->timer      = 0x20;
    shot->angle      = func_801F3320(&SELF(Actor)->pos.x.fixed, &SELF(Actor)->vx);
}
