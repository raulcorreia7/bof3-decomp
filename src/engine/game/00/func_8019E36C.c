#include "game_00.h"

MATCH void func_8019E36C(void) {
    s32 add;
    s16 dist;
    s16 limit;

    add             = TASK(Actor)->vz + TASK(Actor)->gravity;
    TASK(Actor)->vz = add;
    COORD_INT(TASK(Actor)->pos.z) += add;
    Script_AnimStepLoop();
    dist  = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    limit = COORD_INT(TASK(Actor)->pos.z);
    if (dist >= limit) {
        Actor_Clear();
        return;
    }
    if ((dist + 256 < limit) || (g_FrameCount & 0x1)) {
        Area_SetDrawMode();
    }
}
