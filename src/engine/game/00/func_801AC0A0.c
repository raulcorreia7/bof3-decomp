#include "game_00.h"

MATCH void func_801AC0A0(s8 tuning_delta) {
    Actor* work;
    s32    buf[4];
    s8     arg;
    s8     step;
    s8     next;

    arg  = tuning_delta;
    step = arg;
    func_801ABF30((VECTOR*)buf, FIELD(u8, g_SpadWork, 0x18u), FIELD(u8, g_SpadWork, 0x1Cu));
    next = step;
    if (arg == 0) {
        next = 1;
    }
    step               = next;
    g_SpadWork->unk_09 = step;
    work               = g_SpadWork;
    work->vx           = (buf[0] - work->x.fixed) / step;
    work->vy           = (buf[1] - work->y.fixed) / step;
    work->vz           = (buf[2] - work->z.part.integer) / step;
}
