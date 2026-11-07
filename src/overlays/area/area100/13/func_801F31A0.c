#include "area100_13.h"

MATCH void func_801F31A0(void) {
    s32    pos[3];
    Actor* work = g_Task;

    pos[0] = work->pos.x.fixed;
    pos[1] = work->pos.y.fixed;
    pos[2] = work->pos.z.fixed;
    func_801F31E8(pos, 0x8000000);
}
