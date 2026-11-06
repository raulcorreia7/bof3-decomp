#include "game_00.h"

MATCH void func_8019B024(void) {
    Actor* work;
    s16    dist;
    s16    counter;
    s32    diff;

    dist    = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    counter = COORD_INT(g_Task->pos.z);
    if ((counter >= dist + 0x80) || (counter < dist) || (g_Task->header.flags & ACTOR_FLAG_OFFSCREEN)) {
        work = g_Task;
        work->header.mode++;
        SND_PlayCue(EMI_CUE_ID(1, 6));
    }
    g_Task->pos.z.fixed += g_Task->vz;
    diff       = g_Task->vz - g_Task->gravity;
    g_Task->vz = diff;
    func_8014D978();
    Area_SetDrawMode();
}
