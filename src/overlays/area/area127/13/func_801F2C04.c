#include "area127_13.h"

MATCH s32 func_801F2C04(void) {
    u8* work;

    work = g_CurrentActor;
    work[0x74] &= 0xFE;
    if (g_Game.members[0].chr.character_id == 5) {
        SYS_SetFlag(g_SceneEventFlags, 0x32);
        Area_SetCellPalette(0x4E, 0x33);
        g_Task->header.flags = 0;
    }
}
