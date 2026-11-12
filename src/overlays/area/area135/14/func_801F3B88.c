#include "area135_14.h"

MATCH void func_801F3B88(void) {
    Actor* work;
    s32    value;

    work              = g_Task;
    value             = work->pos.z.fixed - 8;
    g_AreaSceneMode   = 0;
    work->pos.z.fixed = value;
    if (value < -0x17F) {
        Area_SetCellPalette(39, 47);
        g_Task->header.step++;
    }
    func_801F3CA8();
}
