#include "game_00.h"

MATCH void func_8019E36C(void) {
    s32 add;
    s16 dist;
    s16 limit;

    add        = g_Task->vz + g_Task->gravity;
    g_Task->vz = add;
    COORD_INT(g_Task->pos.z) += add;
    Actor_StepAnimLoop();
    dist  = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    limit = COORD_INT(g_Task->pos.z);
    if (dist >= limit) {
        Actor_Clear();
        return;
    }
    if ((dist + 256 < limit) || (g_FrameCount & 0x1)) {
        Area_SetDrawMode();
    }
}
