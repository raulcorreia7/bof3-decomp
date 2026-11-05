#include "game_00.h"

MATCH void func_8019E36C(void) {
    s32 add;
    s16 dist;
    s16 limit;

    add                    = g_Task->vz + g_Task->gravity;
    g_Task->vz             = add;
    g_Task->z.part.integer = (u16)(g_Task->z.part.integer + add);
    func_8014D978();
    dist  = Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed);
    limit = g_Task->z.part.integer;
    if (dist >= limit) {
        Actor_Clear();
        return;
    }
    if ((dist + 0x100 < limit) || (g_FrameCount & 1)) {
        Area_SetDrawMode();
    }
}
