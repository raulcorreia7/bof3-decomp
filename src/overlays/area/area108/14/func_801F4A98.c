#include "area108_14.h"

MATCH void func_801F4A98(void) {
    g_CurrentActor->interaction_flags &= 0xFE;
    if (g_CharSlot[D_80145F09] == 5) {
        SYS_SetFlag(g_SceneEventFlags, 0x30U);
        Area_SetCellPalette(1, 0xB);
        g_Task->header.flags = 0;
    }
}
