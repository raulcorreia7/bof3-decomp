#include "game_00.h"

MATCH void func_801AC0A0(s8 tuning_delta) {
    Actor* work;
    s32    buf[4];
    s8     arg;
    s8     step;
    s8     next;

    arg  = tuning_delta;
    step = arg;
    func_801ABF30((VECTOR*)buf, FIELD(u8, g_Task, 0x18u), FIELD(u8, g_Task, 0x1Cu));
    next = step;
    if (arg == 0) {
        next = 1;
    }
    step           = next;
    g_Task->unk_09 = step;
    work           = g_Task;
    work->vx       = (buf[0] - work->pos.x.fixed) / step;
    work->vy       = (buf[1] - work->pos.y.fixed) / step;
    work->vz       = (buf[2] - COORD_INT(work->pos.z)) / step;
}
