#include "area139_13.h"

MATCH s32 func_801F42F4(void) {
    u8* work;

    work = g_CurrentActor;
    work[0x74] &= 0xFE;
    if (g_Game.members[0].chr.character_id == CHAR_ID_MOMO) {
        SYS_SetFlag(g_SceneEventFlags, 77);
        Area_SetCellPalette(4, 13);
        g_Task->header.flags = 0;
    }
}
