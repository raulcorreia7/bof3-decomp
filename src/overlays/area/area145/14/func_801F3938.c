#include "area145_14.h"

MATCH void func_801F3938(void) {
    Actor* work;
    u32    pos[3];

    work   = g_Task;
    pos[0] = work->pos.x.fixed;
    pos[1] = work->pos.y.fixed;
    pos[2] = work->pos.z.fixed;
    func_801F3980(pos);
}
