#include "game_00.h"

MATCH void func_8019E884(void) {
    Actor* work;
    s32    add;
    s16    dist;

    add                    = g_Task->vz + g_Task->gravity;
    g_Task->vz             = add;
    g_Task->z.part.integer = (u16)(g_Task->z.part.integer + add);
    func_8014D978();
    work = g_Task;
    dist = Area_SampleHeight(work->x.fixed, work->y.fixed);
    if (work->z.part.integer < dist) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
