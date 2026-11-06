#include "area135_14.h"

MATCH void func_801F3B88(void) {
    Actor* work;
    s32    value;

    work            = g_Task;
    value           = work->z.fixed - 8;
    g_AreaSceneMode = 0;
    work->z.fixed   = value;
    if (value < -0x17F) {
        Area_SetCellPalette(0x27, 0x2F);
        g_Task->header.step++;
    }
    func_801F3CA8();
}
