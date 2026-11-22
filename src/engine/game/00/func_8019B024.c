#include "game_00.h"

MATCH void func_8019B024(void) {
    Actor* work;
    s16    dist;
    s16    counter;
    s32    diff;

    dist    = Area_HeightSample(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    counter = COORD_INT(g_Task->pos.z);
    if ((counter >= dist + 0x80) || (counter < dist) || (g_Task->header.flags & ACTOR_FLAG_OFFSCREEN)) {
        work = g_Task;
        work->header.mode++;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
    }
    g_Task->pos.z.fixed += g_Task->vz;
    diff       = g_Task->vz - g_Task->gravity;
    g_Task->vz = diff;
    Script_AnimStepLoop();
    Area_SetDrawMode();
}
