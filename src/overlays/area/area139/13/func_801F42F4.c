#include "area139_13.h"

MATCH void func_801F42F4(void) {
    u8* work;

    work = g_CurrentActor;
    work[0x74] &= 0xFE;
    if (D_80145F09[0][0] == 5) {
        SYS_SetFlag(g_SceneEventFlags, 0x4D);
        Area_SetCellPalette(4, 0xD);
        g_Task->header.flags = 0;
    }
}
