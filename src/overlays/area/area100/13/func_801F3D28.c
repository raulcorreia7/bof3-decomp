#include "area100_13.h"

MATCH void func_801F3D28(void) {
    s32    pos[3];
    Actor* work = g_Task;

    pos[0] = work->pos.x.fixed;
    pos[1] = work->pos.y.fixed;
    pos[2] = work->pos.z.fixed;
    func_801F3D70(pos);
}
