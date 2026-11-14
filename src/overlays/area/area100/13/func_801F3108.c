#include "area100_13.h"

MATCH void func_801F3108(void) {
    Actor*   actor = g_Task;
    Point3l pos;

    actor->gravity += 0x100000;
    actor->vz += actor->gravity;
    pos.x = actor->pos.x.fixed;
    pos.y = actor->pos.y.fixed;
    pos.z = actor->pos.z.fixed;
    func_801F31E8(&pos, actor->vz);
    if (g_Task->vz > 0x07FFFFFF) {
        g_Task->header.mode++;
    }
}
