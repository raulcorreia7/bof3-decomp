#include "area173_14.h"

MATCH void func_801F3714(void) {
    s16* slot;

    slot       = &D_1F800038;
    *slot      = -0x180;
    D_1F80003A = 0;
    func_801F3954(0);
    *slot = 384;
    func_801F3954(1);
    *slot      = 0;
    D_1F80003A = g_Task->timer << 3;
    func_801F3954(2);
    g_Task->timer++;
    if (g_Task->timer >= 49) {
        SYS_SetFlag(g_SceneEventFlags, 129);
        Area_SetCellPalette(48, 113);
        Actor_Clear();
    }
}
