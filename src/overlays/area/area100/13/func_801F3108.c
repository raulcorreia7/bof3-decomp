#include "area100_13.h"

MATCH void func_801F3108(void) {
    Actor* actor = g_SpadWork;
    Vec3i pos;

    actor->gravity += 0x100000;
    actor->vz += actor->gravity;
    pos.x = actor->x.fixed;
    pos.y = actor->y.fixed;
    pos.z = actor->z.fixed;
    func_801F31E8(&pos, actor->vz);
    if (g_SpadWork->vz > 0x07FFFFFF) {
        g_SpadWork->unk_01++;
    }
}
