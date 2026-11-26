#include "game_00.h"

MATCH u8 func_801ABD68(s32 pos_x, s32 pos_y, s32 step_count, void* deltas) {
    Actor* work;
    Actor* work2;
    Actor* work3;
    s16    dist;
    s16    dz;
    s32    dx;
    s32    dy;
    u8     count;
    u8     ret;

    work  = SELF(Actor);
    count = step_count;
    ret   = work->direction;
    dx    = pos_x - work->pos.x.fixed;
    dy    = pos_y - work->pos.y.fixed;
    dist  = Area_HeightSample(pos_x, pos_y);
    work2 = SELF(Actor);
    dz    = dist - COORD_INT(work2->pos.z);
    if (FIELD(u8, deltas, 0x4u) != 0) {
        count               = count ? count : 1;
        work2->timer        = count;
        SELF(Actor)->unk_0A = count + 1;
        work3               = SELF(Actor);
        work3->header.flags |= ACTOR_FLAG_STEP_MOVE;
        setVector(work3, dx / count, dy / count, dz / count);
    }
    return ret;
}
