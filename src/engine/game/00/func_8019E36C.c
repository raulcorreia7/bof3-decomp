#include "game_00.h"

MATCH void func_8019E36C(void) {
    s32 add;
    s16 dist;
    s16 limit;

    add                    = g_Task->vz + g_Task->gravity;
    g_Task->vz             = add;
    COORD_INT(g_Task->z) = (u16)(COORD_INT(g_Task->z) + add);
    func_8014D978();
    dist  = Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed);
    limit = COORD_INT(g_Task->z);
    if (dist >= limit) {
        Actor_Clear();
        return;
    }
    if ((dist + 0x100 < limit) || (g_FrameCount & 1)) {
        Area_SetDrawMode();
    }
}
