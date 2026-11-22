#include "area102_13.h"

MATCH void func_801F32A8(void) {
    Actor* gate;
    Actor* level;
    Actor* from;
    Actor* position;
    Actor* state;
    u8     countdown;
    s32    distance;
    s16    offset_distance;

    level                      = TASK(Actor);
    countdown                  = D_801F395C[(COORD_INT(level->pos.x) & 1) | ((COORD_INT(level->pos.y) & 1) << 1)];
    level->unk_0A              = countdown;
    level->timer               = countdown;
    from                       = TASK(Actor);
    distance                   = Area_HeightSample(from->pos.x.fixed, from->pos.y.fixed);
    position                   = TASK(Actor);
    COORD_INT(position->pos.z) = distance;
    offset_distance            = Area_HeightSample(position->pos.x.fixed + 0x8000, position->pos.y.fixed - 0x8000);
    gate                       = TASK(Actor);
    if (COORD_INT(gate->pos.z) < offset_distance) {
        gate->vx = 0;
        gate->vy = 1;
    } else {
        gate->vx = 1;
        gate->vy = 0;
    }
    state = TASK(Actor);
    state->header.step++;
}
