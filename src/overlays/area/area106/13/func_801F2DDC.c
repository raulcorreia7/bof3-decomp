#include "area106_13.h"

MATCH void func_801F2DDC(void) {
    if (g_Task->timer != 0) {
        func_801F2F38(1, D_801F3E90[g_Task->timer] << 4);
        g_Task->timer += 1;
    }
    if (g_Task->timer == 0x17) {
        SYS_SetFlag(g_SceneEventFlags, 0x50);
        Area_SetCellPalette(0x13, 0x25);
        g_Task->timer = 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x4F) != 0) {
        if (g_Task->unk_0A < 0x19) {
            func_801F31DC(D_801F3E90[0x2C + g_Task->unk_0A] << 2, D_801F3E90[0x48 + (g_Task->unk_0A >> 1)]);
        }
        func_801F33D4(g_Task->unk_0A);
    }
    g_Task->unk_0A += 1;
    if (g_Task->unk_0A >= 0x31) {
        Actor_Clear();
    }
}
