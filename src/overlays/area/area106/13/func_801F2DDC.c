#include "area106_13.h"

MATCH void func_801F2DDC(void) {
    if (TASK(Actor)->timer != 0) {
        func_801F2F38(1, D_801F3E90[TASK(Actor)->timer] << 4);
        TASK(Actor)->timer += 1;
    }
    if (TASK(Actor)->timer == 0x17) {
        SYS_SetFlag(g_SceneEventFlags, 0x50);
        Area_CellSetPalette(0x13, 0x25);
        TASK(Actor)->timer = 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x4F) != 0) {
        if (TASK(Actor)->unk_0A < 0x19) {
            func_801F31DC(D_801F3E90[0x2C + TASK(Actor)->unk_0A] << 2, D_801F3E90[0x48 + (TASK(Actor)->unk_0A >> 1)]);
        }
        func_801F33D4(TASK(Actor)->unk_0A);
    }
    TASK(Actor)->unk_0A += 1;
    if (TASK(Actor)->unk_0A >= 0x31) {
        Actor_Clear();
    }
}
