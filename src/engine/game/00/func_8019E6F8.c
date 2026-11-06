#include "game_00.h"

MATCH void func_8019E6F8(void) {
    Actor* work;
    s32    value;

    func_8014D978();
    work     = g_Task;
    value    = work->vz + work->gravity;
    work->vz = value;
    COORD_INT(work->pos.z) += value;
    if (Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed) >= (s16)COORD_INT(work->pos.z)) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
