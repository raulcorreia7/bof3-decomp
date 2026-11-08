#include "area116_13.h"

MATCH void func_801F2F30(void) {
    Actor* work;
    s32    pos[3];

    work   = g_Task;
    pos[0] = work->pos.x.fixed;
    pos[1] = work->pos.y.fixed;
    pos[2] = work->pos.z.fixed;
    Area_DrawLightPillar(pos);
}
