#include "area112_13.h"

/* func_801F3EA4 */
MATCH void Area_DrawActorLightPillar(void) {
    s32    pos[3];
    Actor* work = g_Task;

    pos[0] = work->pos.x.fixed;
    pos[1] = work->pos.y.fixed;
    pos[2] = work->pos.z.fixed;
    Area_DrawLightPillar(pos);
}
