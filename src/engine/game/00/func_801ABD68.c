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

    work  = g_Task;
    count = step_count;
    ret   = work->direction_08;
    dx    = pos_x - work->x.fixed;
    dy    = pos_y - work->y.fixed;
    dist  = Area_SampleHeight(pos_x, pos_y);
    work2 = g_Task;
    dz    = dist - COORD_INT(work2->z);
    if (FIELD(u8, deltas, 0x4u) != 0) {
        count          = count ? count : 1;
        work2->unk_09  = count;
        g_Task->unk_0A = count + 1;
        work3          = g_Task;
        work3->header.flags |= ACTOR_FLAG_STEP_MOVE;
        work3->vx = dx / count;
        work3->vy = dy / count;
        work3->vz = dz / count;
    }
    return ret;
}
