#include "area084_13.h"

MATCH void func_801F2C04(void) {
    u8* work;

    work = g_CurrentActor;
    work[0x74] &= 0xFE;
    if (D_80145F09 == 5) {
        SYS_SetFlag(g_SceneEventFlags, 0x31);
        Area_SetCellPalette(9, 0x10);
        g_Task->header.flags = 0;
    }
}
